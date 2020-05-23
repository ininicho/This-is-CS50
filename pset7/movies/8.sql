SELECT name FROM people
JOIN stars ON id = person_id
WHERE movie_id = (SELECT id FROM movies
WHERE title = "Toy Story");