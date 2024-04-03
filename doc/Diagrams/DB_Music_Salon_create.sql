-- Created by Vertabelo (http://vertabelo.com)
-- Last modification date: 2021-03-26 19:45:00.615

-- tables
-- Table: Compact_Disk_info
CREATE TABLE Compact_Disk_info (
    ID integer NOT NULL CONSTRAINT Compact_Disk_info_pk PRIMARY KEY,
    dateOfCreate date,
    producerName text,
    price integer
);

-- Table: Compact_Sale_Info
CREATE TABLE Compact_Sale_Info (
    ID integer NOT NULL CONSTRAINT ID PRIMARY KEY,
    count integer,
    dateOfOperation date,
    codeOfOperation integer NOT NULL,
    Compact_Disk_info_ID integer NOT NULL,
    CONSTRAINT Compact_Sale_Info_Compact_Disk_info FOREIGN KEY (Compact_Disk_info_ID)
    REFERENCES Compact_Disk_info (ID)
);

-- Table: producer_info
CREATE TABLE producer_info (
    ID integer NOT NULL CONSTRAINT producer_info_pk PRIMARY KEY,
    author text,
    signer text,
    name integer,
    Compact_Disk_info_ID integer NOT NULL,
    CONSTRAINT producer_info_Compact_Disk_info FOREIGN KEY (Compact_Disk_info_ID)
    REFERENCES Compact_Disk_info (ID)
);

-- End of file.

