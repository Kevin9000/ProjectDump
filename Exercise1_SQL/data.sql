CREATE TABLE Cittadino(
	IDcittadino			int(5)			primary key auto_increment,
	nome				varchar(20)		not null   				  ,
	cognome				varchar(20)		not null		   		  ,
	dataNascita			date			not null   			      ,
	via					varchar(20)		not null	       		  ,
	civico				int(4)			not null	       		  ,
	quartiere			varchar(20)		not null	       		  ,
	numeroTelefonico	int(15)			not null		   				  
);
INSERT INTO `cittadino` (`IDcittadino`, `nome`, `cognome`, `dataNascita`, `via`, `civico`, `quartiere`, `numeroTelefonico`) VALUES (NULL, 'Kia ', 'Charlton', '2002-12-23', 'Differ Avenue', '45', 'Upper South Chailp', '2100560080'), (NULL, 'Cindy ', 'Maldonado', '1995-12-23', 'Chapel Moor', '5', 'West Hunnab', '1046556008');
INSERT INTO `cittadino` (`IDcittadino`, `nome`, `cognome`, `dataNascita`, `via`, `civico`, `quartiere`, `numeroTelefonico`) VALUES (NULL, 'Serenity ', 'Soto', '2003-03-13', 'Loxley Park', '80', 'Prarithig North', '2111440080'), (NULL, 'Julia ', 'Huber', '1995-08-15', 'Wenger Road', '20', 'Shradexem Acre', '1046544008');
INSERT INTO `cittadino` (`IDcittadino`, `nome`, `cognome`, `dataNascita`, `via`, `civico`, `quartiere`, `numeroTelefonico`) VALUES (NULL, 'Kevin', 'Wang', '2002-02-28', 'via Roma', '6', 'Shradexem Acre', '860489412'), (NULL, 'Andrea', 'Perna', '2002-01-31', 'via Roma', '4', 'Shradexem Acre', '860489412');

CREATE TABLE Cane(
	IDcane			int(5)				primary key auto_increment									,
	nome			varchar(20)			not null   				  									,
	razza			varchar(20)			not null   				  									,
	sesso			varchar(1)			not null   				  									,
	anni			int(2)              not null           				  							,
	IDcittadino		int(5)              references Cittadino(IDcittadino)
);
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `IDcittadino`) VALUES (NULL, 'A.J.', 'siberian husky', 'M', '0', '2'), (NULL, 'Adler', 'siberian husky', 'F', '2', NULL);
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `IDcittadino`) VALUES (NULL, 'Aslan', 'Akita', 'M', '0', '1'), (NULL, 'Apollo', 'Bassador', 'F', '2', '3');
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `IDcittadino`) VALUES (NULL, 'Flash', 'Chiwawa', 'F', '2', '5'), (NULL, 'Gilda', 'Bull dog', 'M', '0', '6');


SELECT cittadino.nome, cittadino.cognome, cane.razza FROM cittadino JOIN cane on cane.IDcittadino=cittadino.IDcittadino and cane.razza="siberian husky";
SELECT cane.nome, cane.razza, cane.sesso, cane.anni, cittadino.via, cittadino.civico from cane JOIN cittadino on cane.IDcittadino=cittadino.IDcittadino and cittadino.via="via Roma" and cittadino.civico="4";
SELECT cittadino.cognome, cittadino.nome, cittadino.numeroTelefonico, cane.anni FROM cittadino NATURAL JOIN cane;
SELECT cane.nome, cane.razza, cane.sesso, cane.anni, cittadino.nome, cittadino.cognome, cittadino.numeroTelefonico FROM cane LEFT JOIN cittadino on cittadino.IDcittadino=cane.IDcittadino;
SELECT cittadino.nome, cittadino.cognome, cittadino.quartiere, cane.nome, cane.razza FROM cane RIGHT JOIN cittadino ON cittadino.IDcittadino = cane.IDcittadino;
SELECT DISTINCT cittadino.nome, cittadino.cognome, cane.nome, cane.razza FROM cittadino LEFT JOIN cane on 1 UNION SELECT DISTINCT cittadino.nome, cittadino.cognome, cane.nome, cane.razza FROM cittadino LEFT JOIN cane on 1;