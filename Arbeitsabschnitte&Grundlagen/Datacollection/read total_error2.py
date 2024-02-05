import csv

eingabe_dateipfad = 'in.txt'
ausgabe_dateipfad = 'ausgabe.csv'

bearbeitete_zeilen = []

with open(eingabe_dateipfad, 'r') as datei:
    zeilen = datei.readlines()

    # for i in range(0, len(zeilen)):
    #    bearbeitete_zeilen.append(zeilen[i].replace("Total Error: ", ""))
    bearbeitete_zeilen =[zeile.strip() for zeile in zeilen]

with open(ausgabe_dateipfad, 'w', encoding='utf-8') as csvfile:
    for zeile in bearbeitete_zeilen:
        werte = zeile.split()
        for wert in werte:
            csvfile.write(f'{wert}\n')
