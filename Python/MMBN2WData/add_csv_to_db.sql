DROP TABLE IF EXISTS standard_chips;
DROP TABLE IF EXISTS mega_chips;
DROP TABLE IF EXISTS giga_chips;

CREATE TABLE standard_chips (
  "ID" INTEGER NOT NULL,
  "Source URL" TEXT NOT NULL,
  "Source File Name" TEXT NOT NULL,
  "Destination File Name" TEXT NOT NULL,
  "Name" TEXT NOT NULL,
  "Damage" TEXT NOT NULL,
  "Letter Codes" TEXT NOT NULL,
  "Memory (MB)" TEXT NOT NULL,
  "Description" TEXT NOT NULL 
);

CREATE TABLE mega_chips (
  "ID" INTEGER NOT NULL,
  "Source URL" TEXT NOT NULL,
  "Source File Name" TEXT NOT NULL,
  "Destination File Name" TEXT NOT NULL,
  "Name" TEXT NOT NULL,
  "Damage" TEXT NOT NULL,
  "Letter Codes" TEXT NOT NULL,
  "Memory (MB)" TEXT NOT NULL,
  "Description" TEXT NOT NULL 
);

CREATE TABLE giga_chips (
  "ID" INTEGER NOT NULL,
  "Source URL" TEXT NOT NULL,
  "Source File Name" TEXT NOT NULL,
  "Destination File Name" TEXT NOT NULL,
  "Name" TEXT NOT NULL,
  "Damage" TEXT NOT NULL,
  "Letter Codes" TEXT NOT NULL,
  "Memory (MB)" TEXT NOT NULL,
  "Description" TEXT NOT NULL 
);

.mode csv
.import standard_chips.csv standard_chips
.import mega_chips.csv mega_chips
.import giga_chips.csv giga_chips
