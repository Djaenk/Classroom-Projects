drop table if exists battles;
drop table if exists trainers;
drop table if exists pokemon;

create table trainers (
  id              integer primary key,
  name            varchar(200)
);

create table pokemon (
  id              integer primary key,
  name            varchar(40) not null,
  trainer_id      integer not null references trainer(id),
  type1           char(10),
  type2           char(10),
  hp              integer,
  attack          integer,
  defense         integer,
  special_attack  integer,
  special_defense integer,
  speed           integer
);

create table battles (
  id              integer primary key,
  winner          integer references pokemon(id),
  loser           integer references pokemon(id)
);

begin;
.mode tabs
.import trainers.tsv trainers
.import pokemon.tsv  pokemon
.import battles.tsv  battles
.mode column
end;
