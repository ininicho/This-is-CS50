SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM
(SELECT movie_id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp") 
WHERE movie_id IN (SELECT movie_id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id 
WHERE people.name = "Helena Bonham Carter"))