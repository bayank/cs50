/* SELECT count(title) FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0);
*/

SELECT count(title) from movies
JOIN ratings on ratings.movie_id = movies.id
WHERE ratings.rating = 10.0;