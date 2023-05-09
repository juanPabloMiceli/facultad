--Ejercicio 2.1

SELECT * FROM Chinook.dbo.Customer;

SELECT * FROM Chinook.dbo.Invoice;

--a
SELECT FirstName, LastName FROM Chinook.dbo.Customer
WHERE Country = 'Brazil';

--b
SELECT Customer.FirstName, Customer.LastName, Invoice.InvoiceDate, Invoice.InvoiceID
FROM Chinook.dbo.Customer
INNER JOIN Chinook.dbo.Invoice ON Customer.CustomerId = Invoice.CustomerId;

--c
SELECT Track.TrackId, AlbumArtist.AlbumId, AlbumArtist.ArtistId 
FROM (
    SELECT Artist.ArtistId, Album.AlbumId
    FROM Chinook.dbo.Album
    INNER JOIN Chinook.dbo.Artist ON Album.ArtistId = Artist.ArtistId
) AS AlbumArtist
INNER JOIN Chinook.dbo.Track ON AlbumArtist.AlbumId = Track.AlbumId;