SELECT AVG(rating) FROM ratings 
JOIN movies ON id = movie_id
WHERE rating IS NOT NULL
AND year = 2012;