CREATE TABLE IF NOT EXISTS Autore(
	IDautore			int(5)			primary key auto_increment,
	nome				varchar(20)     not null   				  ,
	cognome				varchar(20)     not null   				  ,
	nazionalità			varchar(20)     not null   				  ,
	dataNascita			date			not null   				  ,
	dataMorte			date			not null   
);

CREATE TABLE IF NOT EXISTS Editore(
	partitaIVA			int(5)			primary key auto_increment  ,
	nomevia				varchar(20)     not null   					,
	civico				int(3)			not null   					,	
	CAP					int(6)			not null   					,
	comune				varchar(20)     not null   
);

CREATE TABLE IF NOT EXISTS Libro(
	ISBN				int(5)				primary key	auto_increment	,
	titolo				varchar(20)			not null   					,
	numeroPagine		int(5)				not null   					,
	argomento			varchar(20)     	not null  					,
	trama				varchar(1000)  	 	not null   					,
	prezzo              float(5)			not null   					,
	annoPubblicazione   date 				not null   					,
	immagineCopertina   varchar(100)		not null   					,
	IDeditore			int(5)				references Autore(IDautore)
);

CREATE TABLE IF NOT EXISTS Scrittura(
	IDlibro			varchar(5)      references Libro(ISBN)     ,
	IDautore		varchar(5)		references Autore(IDautore),
	primary key(IDlibro, IDautore)
);

INSERT INTO `autore` (`IDautore`, `nome`, `cognome`, `nazionalità`, `dataNascita`, `dataMorte`) VALUES (NULL, 'J.K.', 'Rowling', 'Inghilterra', '1965-07-31', '2045-06-03');
INSERT INTO `autore` (`IDautore`, `nome`, `cognome`, `nazionalità`, `dataNascita`, `dataMorte`) VALUES (NULL, 'Dante ', 'Alighieri', 'italiana', '1265-08-31', '1340-04-28'), (NULL, 'Giacomo', 'Leopardi', 'italiana', '1800-06-21', '1880-06-20')
INSERT INTO `editore` (`partitaIVA`, `nomevia`, `civico`, `CAP`, `comune`) VALUES (NULL, 'via roma', '80', '27100', 'Pavia');
INSERT INTO `editore` (`partitaIVA`, `nomevia`, `civico`, `CAP`, `comune`) VALUES (NULL, 'via pippo', '98', '37100', 'Milano')
INSERT INTO `libro` (`ISBN`, `titolo`, `numeroPagine`, `argomento`, `trama`, `prezzo`, `annoPubblicazione`, `immagineCopertina`, `IDeditore`) VALUES (NULL, 'Guerra filosofale', '250', 'fantasy', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut orci massa, semper ac molestie nec, accumsan quis sapien. Pellentesque vitae diam sit amet odio laoreet sollicitudin nec vel nisl. Ut vulputate gravida nibh non congue. Duis quis nulla condimentum, consectetur felis et, efficitur nisl. Phasellus sagittis lorem id nisi molestie, nec ornare tortor hendrerit. Morbi porta est non elementum dapibus. Nam eu lorem lobortis, finibus sapien vel, dictum ante. Phasellus eget blandit arcu, congue suscipit dui. Praesent feugiat lacinia tortor, ac faucibus tellus tristique ac. Maecenas in volutpat lorem.', '18.50', '2015-06-13', 'user/pippo/file.png', '1'), (NULL, 'Harry Potter e la camera dei segreti', '200', 'fantasy', 'Cras bibendum tellus vel orci venenatis commodo. Quisque et sodales mauris. Vestibulum vehicula iaculis nunc ut euismod. Fusce feugiat rutrum erat a rhoncus. Maecenas leo turpis, imperdiet ut mauris eget, sodales pharetra neque. Nunc sapien mi, cursus et lobortis eget, convallis in mi. Quisque vehicula hendrerit felis, et tincidunt elit feugiat et. Mauris lectus purus, laoreet varius metus et, posuere tempus neque. Ut in sapien facilisis, lacinia lorem id, auctor lorem. Sed fringilla gravida felis sit amet molestie. Aenean ex nisi, scelerisque eget est id, sagittis convallis est. Integer suscipit euismod nisl, elementum consectetur nisi lobortis a. Nulla facilisi. Nulla commodo ligula quis ante ultricies egestas. Nam mi nisl, euismod et sapien sed, pulvinar auctor risus. Donec eu dignissim ligula.', '20.00', '2012-06-13', 'user/pluto/file.png', '1');
INSERT INTO `libro` (`ISBN`, `titolo`, `numeroPagine`, `argomento`, `trama`, `prezzo`, `annoPubblicazione`, `immagineCopertina`, `IDeditore`) VALUES (NULL, 'Fantasy fairy', '300', 'fantasy', 'Donec non tellus congue, mollis turpis sed, blandit eros. Maecenas luctus leo a ex hendrerit gravida. Cras iaculis vel elit a hendrerit. In cursus diam tortor, sit amet maximus ex dignissim id. In lobortis erat ut sodales fermentum. Suspendisse potenti. Maecenas congue arcu sapien, nec malesuada mauris laoreet eget. Vestibulum sagittis magna a tortor tincidunt, ac malesuada velit euismod. Nullam sed quam at sapien rutrum vehicula.', '18.00', '2020-06-13', './utente/pizzo/immagine.png', '1');
INSERT INTO `libro` (`ISBN`, `titolo`, `numeroPagine`, `argomento`, `trama`, `prezzo`, `annoPubblicazione`, `immagineCopertina`, `IDeditore`) VALUES (NULL, 'Sistemi e Reti', '450', 'Sistemi', 'Ciao', '50.00', '2018-06-25', './utente/sistemi/img.png', '2')
INSERT INTO `scrittura` (`IDlibro`, `IDautore`) VALUES ('1', '1'), ('2', '1');
INSERT INTO `scrittura` (`IDlibro`, `IDautore`) VALUES ('4', '3')

SELECT DISTINCT libro.titolo, libro.argomento, libro.prezzo from libro, autore, scrittura WHERE autore.nome="J.K" and autore.cognome="Rowling" and autore.IDautore=scrittura.IDautore;
SELECT COUNT(*) from editore, libro where libro.argomento="fantasy" and (SELECT EXTRACT(YEAR from libro.annoPubblicazione))='2020';
SELECT libro.titolo, autore.nome, autore.cognome, libro.argomento, libro.trama, libro.prezzo from libro, autore where libro.titolo like "Guerra%";
SELECT autore.cognome, autore.nome, autore.dataNascita, autore.dataMorte from autore where autore.nazionalità="italiana" ORDER by autore.cognome;
SELECT libro.titolo, autore.nome, autore.cognome, libro.numeroPagine, libro.immagineCopertina from libro, autore, editore, scrittura where libro.argomento="sistemi" and libro.IDeditore=editore.partitaIVA and editore.partitaIVA="2" and scrittura.IDlibro=libro.ISBN and scrittura.IDautore=autore.IDautore ORDER by libro.annoPubblicazione DESC;
SELECT libro.titolo, autore.nome, autore.cognome, libro.trama, libro.prezzo from libro, autore, scrittura where libro.numeroPagine=(SELECT MAX(libro.numeroPagine) from libro) and scrittura.IDautore=autore.IDautore and scrittura.IDlibro=libro.ISBN;