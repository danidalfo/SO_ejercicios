DROP DATABASE IF EXISTS dramatic_shark;
CREATE DATABASE dramatic_shark;

USE dramatic_shark;

CREATE TABLE jugadores (
id_j INTEGER PRIMARY KEY NOT NULL,
nombre TEXT,
password TEXT,
color_pantalones TEXT
)ENGINE = InnoDB;

CREATE TABLE partidas (
id_p INTEGER PRIMARY KEY NOT NULL,
fecha TEXT,
duracion INTEGER,
ganador TEXT   
)ENGINE = InnoDB;

CREATE TABLE relacion (
  jugador INTEGER NOT NULL,
  partida INTEGER NOT NULL, 
  FOREIGN KEY (jugador) REFERENCES   jugadores(id_j),
  FOREIGN KEY (partida) REFERENCES   partidas(id_p)
)ENGINE = InnoDB;


INSERT INTO jugadores (id_j, nombre, password, color_pantalones)
VALUES (1,'Lluis',mimara,rojo);

INSERT INTO jugadores (id_j, nombre, password, color_pantalones)
VALUES (2,'Marta',mipara,lila);

INSERT INTO jugadores (id_j, nombre, password, color_pantalones)
VALUES (3,'Susana',mitio,blue);

INSERT INTO partidas (id_p, fecha, duracion, ganador)
VALUES (1,'09052017',15,Marta);

INSERT INTO partidas (id_p, fecha, duracion, ganador)
VALUES (2,'19062017',45,Lluis);

INSERT INTO relacion VALUES (1,2);
INSERT INTO relacion VALUES (2,2);
INSERT INTO relacion VALUES (2,1);
INSERT INTO relacion VALUES (3,1);