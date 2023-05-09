-- 1. Cuantos empleados fueron contratados por anio
SELECT YEAR(Employee.HireDate) AS HireYear, COUNT(*) AS TotalEmployees 
FROM Chinook.dbo.Employee
GROUP BY YEAR(Employee.HireDate);

-- 2. Cantidad de canciones de Rock por artista
SELECT Artist.Name, COUNT(*) AS TotalCancionesDeRock 
FROM Chinook.dbo.Artist
INNER JOIN Chinook.dbo.Album ON Artist.ArtistId = Album.ArtistId
INNER JOIN Chinook.dbo.Track ON Album.AlbumId = Track.AlbumId
INNER JOIN Chinook.dbo.Genre ON Genre.GenreId = Track.GenreId
WHERE Genre.Name = 'Rock'
GROUP BY Artist.Name;

-- 3. Artistas que han ganado mas de 100 pesos en total
WITH GananciasPorArtista AS (
    SELECT Artist.Name, SUM(Track.UnitPrice) AS GananciasTotales 
    FROM Chinook.dbo.Track
    INNER JOIN Chinook.dbo.Album ON Album.AlbumId = Track.AlbumId
    INNER JOIN Chinook.dbo.Artist ON Artist.ArtistId = Album.ArtistId
    GROUP BY Artist.Name
)
SELECT * 
FROM GananciasPorArtista
WHERE GananciasPorArtista.GananciasTotales > 100;

-- 4. Para cada artista, la duracion en segundos de su cancion mas extensa y la diff con su cancion mas corta

SELECT Artist.ArtistId, MAX(Track.Milliseconds / 1000) AS SegundosCancionMasLarga, (MAX(Track.Milliseconds)- MIN(Track.Milliseconds))/1000 AS MaximoDeltaSegundos
FROM Chinook.dbo.Track
INNER JOIN Chinook.dbo.Album ON Album.AlbumId = Track.AlbumId
INNER JOIN Chinook.dbo.Artist ON Artist.ArtistId = Album.ArtistId
GROUP BY Artist.ArtistId
ORDER BY Artist.ArtistId;

-- 5. Cuanto gasto cada cliente en cada genero

SELECT Customer.CustomerId, Genre.GenreId, SUM(InvoiceLine.UnitPrice * InvoiceLine.Quantity) AS GastoPorGenero
FROM Chinook.dbo.Track
INNER JOIN Chinook.dbo.Genre ON Track.GenreId = Genre.GenreId
INNER JOIN Chinook.dbo.InvoiceLine ON Track.TrackId = InvoiceLine.TrackId
INNER JOIN Chinook.dbo.Invoice ON Invoice.InvoiceId = InvoiceLine.InvoiceId
INNER JOIN Chinook.dbo.Customer ON Customer.CustomerId = Invoice.CustomerId
GROUP BY Customer.CustomerId, Genre.GenreId;

-- 6. Playlists que contengan los tracks de mayor duracion

SELECT Playlist.PlaylistId
FROM Chinook.dbo.Playlist
INNER JOIN Chinook.dbo.PlaylistTrack ON Playlist.PlaylistId = PlaylistTrack.PlaylistId
INNER JOIN Chinook.dbo.Track ON Track.TrackId = PlaylistTrack.TrackId
WHERE Track.Milliseconds = (SELECT MAX(Track.Milliseconds) AS MaximaDuracion
    FROM Chinook.dbo.Playlist
    INNER JOIN Chinook.dbo.PlaylistTrack ON Playlist.PlaylistId = PlaylistTrack.PlaylistId
    INNER JOIN Chinook.dbo.Track ON Track.TrackId = PlaylistTrack.TrackId);