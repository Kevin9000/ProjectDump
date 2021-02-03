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
INSERT INTO `cittadino` (`IDcittadino`, `nome`, `cognome`, `dataNascita`, `via`, `civico`, `quartiere`, `numeroTelefonico`) VALUES (NULL, 'Mario', 'Rossi', '2002-06-28', 'via Roma', '98', 'centro', '450841897');

CREATE TABLE Cane(
	IDcane			int(5)				primary key auto_increment									,
	nome			varchar(20)			not null   				  									,
	razza			varchar(20)			not null   				  									,
	sesso			varchar(1)			not null   				  									,
	anni			int(2)              not null           				  							,
	origine 		varchar(20)			not null													,
	prezzo			int(5)				not null													,
	IDcittadino		int(5)              references Cittadino(IDcittadino)
);
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `origine`, `prezzo`, `IDcittadino`) VALUES (NULL, 'A.J.', 'siberian husky', 'M', '0', 'privato', '400', '2'), (NULL, 'Adler', 'siberian husky', 'F', '2', 'canile', '400', NULL);
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `origine`, `prezzo`, `IDcittadino`) VALUES (NULL, 'Aslan', 'Akita', 'M', '0', 'privato', '200', '1'), (NULL, 'Apollo', 'Bassador', 'F', '2', 'privato', '400', '3');
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `origine`, `prezzo`, `IDcittadino`) VALUES (NULL, 'Flash', 'Chiwawa', 'F', '2', 'privato', '100', '5'), (NULL, 'Gilda', 'Bull dog', 'M', '0', 'privato', '600', '6');
INSERT INTO `cane` (`IDcane`, `nome`, `razza`, `sesso`, `anni`, `origine`, `prezzo`, `IDcittadino`) VALUES (NULL, 'Fresh', 'Akita', 'F', '1', 'Privato', '1000', '7'), (NULL, 'Shan', 'Bull dog', 'F', '0', 'Privato', '900', '7');

select count(*) from cane WHERE cane.razza='siberian husky';
SELECT SUM(cane.prezzo) from cane, cittadino WHERE cane.IDcittadino=cittadino.IDcittadino and cittadino.nome="Mario" and cittadino.cognome="Rossi";
SELECT MIN(cane.prezzo) from cane where cane.razza='akita';
SELECT AVG(cane.prezzo) from cane where cane.anni='0';
SELECT cane.nome, cane.razza, cane.sesso, cane.anni FROM cane INNER JOIN(SELECT MAX(cane.anni) AS maxCaneAnni from cane) info on cane.anni=info.maxCaneAnni;
SELECT COUNT(*) from cane, cittadino where cane.IDcittadino=cittadino.IDcittadino and cittadino.quartiere="centro" UNION SELECT AVG(cane.anni) from cane, cittadino where cane.IDcane=cittadino.IDcittadino and cittadino.quartiere="centro";