using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Dziennik
{
    /// <summary>
    /// Logika interakcji dla klasy DodajUcznia.xaml
    /// </summary>
    public partial class DodajUcznia : Window
    {
        public Uczen NewUczen { get; private set; }
        private Random random;

        public DodajUcznia()
        {
            InitializeComponent();
            random = new Random();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            NewUczen = new Uczen
            {
                Imie = ImieTextBox.Text,
                Nazwisko = NazwiskoTextBox.Text,
                Opis = OpisTextBox.Text,
                Ocena = int.Parse(OcenaTextBox.Text)
            };
            DialogResult = true;
        }
        private void LosujButton_Click(object sender, RoutedEventArgs e)
        {
            if (ImieTextBox.Text.Equals("Wojciech") || ImieTextBox.Text.Equals("Wojtek"))
            {
                OcenaTextBox.Text = 5.ToString();
            }
            else
            {
                int randomGrade = random.Next(1, 7); // Zakres ocen od 1 do 5
                OcenaTextBox.Text = randomGrade.ToString();
            }
        }
    }
}