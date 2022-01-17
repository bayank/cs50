
SELECT name FROM people
join stars on stars.person_id = people.id
join movies on stars.movie_id = movies.id
where movies.title = "Toy Story";