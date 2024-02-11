import csv
import matplotlib.pyplot as plt

def plot_csv_first_row(csv_file_path):
    with open(csv_file_path, 'r') as file:
        reader = csv.reader(file)
        header = next(reader)  # Lese die Header-Zeile

        if not header:
            print("Die CSV-Datei ist leer.")
            return

        # Extrahiere die erste Reihe der CSV
        first_row_data = [float(row[0]) for row in reader]

        # Erstelle ein Liniendiagramm
        plt.plot(first_row_data)

        # Beschriftung und Anzeige des Diagramms
        plt.title('in '+epoch+' epoch '+images+' images ' + lr+' learningrate')
        plt.xlabel('Index')
        plt.ylabel('Total Error')  # Verwende den Header als Y-Achsenbeschriftung
        plt.show()

# Beispielaufruf mit einer CSV-Datei namens "beispiel.csv"
epoch = input()
images = input()
lr = input()
plot_csv_first_row('ausgabe.csv')

