import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd
# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT name, shares FROM portfolio WHERE id=?", session['user_id'])

    n = len(rows)

    stocks = []
    cash_row = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
    cash = float(cash_row[0]['cash'])
    total_cash = cash

    for i in range(n):
        symbol = rows[i]['name']
        shares = int(rows[i]['shares'])

        if shares == 0:
            pass

        temp = lookup(symbol)
        name = temp['name']
        price = temp['price']
        total = price * shares
        stocks.append([symbol, name, shares, usd(price), usd(total)])
        total_cash += total

    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(total_cash))
    # stocks = [symbol, shares, price, name, total]


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check if symbol is valid
        if not lookup(request.form.get("symbol")):
            return apology("symbol not valid", 403)

        # Check if shares is an integer
        elif int(request.form.get("shares")) < 1:
            return apology("at least buy 1", 403)

        # Calculate stock price
        stock = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        total_price = shares * stock['price']

        # Query user cash
        cash_query = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = float(cash_query[0]['cash'])

        # Check if user has enough cash
        if total_price > cash:
            return apology("not enough cash", 403)

        else:
            db.execute("INSERT INTO stocks_buy (id, buy_name, buy_price, buy_shares) VALUES (?,?,?,?)", (session['user_id'], stock['symbol'], stock['price'], shares))
            cash = cash - total_price
            db.execute("UPDATE users SET cash=? WHERE id=?", (cash, session['user_id']))

            portfolio = db.execute("SELECT name FROM portfolio WHERE id=?", session['user_id'])

            for i in range(len(portfolio)):
                if stock['symbol'] == portfolio[i]['name']:
                    current_shares = db.execute("SELECT shares FROM portfolio WHERE id=? AND name=?", (session['user_id'], stock['symbol']))
                    total_shares = shares + int(current_shares[0]['shares'])
                    db.execute("UPDATE portfolio SET shares=? WHERE (id=? AND name=?)", (total_shares, session['user_id'], stock['symbol']))
                    return redirect("/")

            db.execute("INSERT INTO portfolio (id, name, shares) VALUES (?,?,?)", (session['user_id'], stock['symbol'], shares))
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    buy_rows = db.execute("SELECT buy_name, buy_price, buy_shares, timestamp FROM stocks_buy WHERE id=?", session['user_id'])
    sell_rows = db.execute("SELECT sell_name, sell_price, sell_shares, timestamp FROM stocks_sell WHERE id=?", session['user_id'])

    buy_list = []
    sell_list = []

    n_buy = len(buy_rows)
    n_sell = len(sell_rows)

    for i in range(n_buy):
        name = buy_rows[i]['buy_name']
        price = buy_rows[i]['buy_price']
        shares = buy_rows[i]['buy_shares']
        time = buy_rows[i]['timestamp']
        buy_list.append([name, price, shares, time])

    for i in range(n_sell):
        name = sell_rows[i]['sell_name']
        price = sell_rows[i]['sell_price']
        shares = sell_rows[i]['sell_shares']
        time = sell_rows[i]['timestamp']
        sell_list.append([name, price, shares, time])

    return render_template("history.html", buy=buy_list, sell=sell_list)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # When user submit input
    if request.method == "POST":

        # Check if input is empty
        if not request.form.get("symbol"):
            return apology("no symbol given", 400)

        symbol = request.form.get("symbol")

        # Check if input is valid in lookup
        if not lookup(symbol):
            return apology("invalid symbol", 403)

        stock_dict = lookup(symbol)

        # Returns quoted with the stock name, symbol, and price
        return render_template("quoted.html",
                                stock_name = stock_dict['name'],
                                stock_symbol = stock_dict['symbol'],
                                stock_price = usd(stock_dict['price']))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Make sure no one is logged on
    session.clear()

    # User submit register button
    if request.method == "POST":

        rows = db.execute("SELECT * FROM users")

        # Ensure username is submitted and not taken
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif request.form.get("username") in rows[0]["username"]:
            return apology("username taken", 403)

        # Ensure password is submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmation is correct
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password confirmation not correct", 403)

        hash_password = generate_password_hash(request.form.get("password"))
        user = request.form.get("username")

        # Inserts username and hashed password to table
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", (user, hash_password))

        # Remember User and redirect to main page
        user_id = db.execute("SELECT id FROM users WHERE username = ?", user)
        session["user_id"] = user_id

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User Submit Form
    if request.method == "POST":

        # Check if no stock selected
        if not request.form.get('symbol'):
            return apology("no stock selected", 403)

        symbol = request.form.get('symbol')
        stock = lookup(symbol)

        # Query shares
        shares_own = db.execute("SELECT shares FROM portfolio WHERE (id=? AND name=?)", (session['user_id'], symbol))

        # Check if shares is inputed
        if not request.form.get('shares'):
            return apology("shares invalid", 403)

        shares = int(request.form.get('shares'))

        # Check if shares not more than owned shares
        if shares < 1 or shares > shares_own[0]['shares']:
            return apology("shares invalid", 403)

        # Insert to stock sell tables
        db.execute("INSERT INTO stocks_sell (id, sell_name, sell_price, sell_shares) VALUES (?,?,?,?)", (session['user_id'], stock['symbol'], stock['price'], shares))
        shares_current = shares_own[0]['shares'] - shares

        # Update portfolio shares
        if shares_current == 0:
            db.execute("DELETE FROM portfolio WHERE (id=? AND name=?)", (session['user_id'], stock['symbol']))
        else:
            db.execute("UPDATE portfolio SET shares=? WHERE (id=? AND name=?)", (shares_current, session['user_id'], stock['symbol']))

        # Update users cash
        cash_row = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
        cash = float(cash_row[0]['cash']) + shares*stock['price']
        db.execute("UPDATE users SET cash=? WHERE id=?", (cash, session['user_id']))

        return redirect("/")

    else:
        stock_rows = db.execute("SELECT name FROM portfolio WHERE id=?", session['user_id'])
        stock_options = []

        for i in range(len(stock_rows)):
            stock_options.append(stock_rows[i]['name'])

        return render_template("sell.html", stocks=stock_options)


@app.route("/change", methods=["GET","POST"])
@login_required
def change():
    if request.method == "POST":

        if not request.form.get("current"):
            return apology("enter current password", 403)
        elif not request.form.get("new"):
            return apology("enter new password", 403)
        elif not request.form.get("confirmation"):
            return apology("enter password confirmation", 403)
        elif request.form.get("new") != request.form.get("confirmation"):
            return apology("password confirmation wrong", 403)
        elif request.form.get("current") == request.form.get("new"):
            return apology("new password must be different", 403)

        password = request.form.get("current")
        query_password = db.execute("SELECT hash FROM users WHERE id=?", session['user_id'])

        if not check_password_hash(query_password[0]['hash'], password):
            return apology("current password incorrect", 403)

        new_password = request.form.get("new")
        hash_password = generate_password_hash(new_password)

        db.execute("UPDATE users SET hash=? WHERE id=?", (hash_password, session['user_id']))

        return redirect("/")
    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
