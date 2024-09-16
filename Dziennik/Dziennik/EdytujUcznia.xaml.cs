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
    /// Logika interakcji dla klasy EdytujUcznia.xaml
    /// </summary>
    public partial class EdytujUcznia : Window
        
    {
        public Uczen EditedUczniowie { get; private set; }
        public EdytujUcznia(Uczen uczen)
        {
            InitializeComponent();
            ImieTextBox.Text = uczen.Imie;
            NazwiskoTextBox.Text = uczen.Nazwisko;
            OpisTextBox.Text = uczen.Opis;
            OcenaTextBox.Text = uczen.Ocena.ToString();
            EditedUczniowie = uczen;
        }

        private void SaveButton_Click(object sender, RoutedEventArgs e)
        {
            EditedUczniowie.Imie = ImieTextBox.Text;
            EditedUczniowie.Nazwisko = NazwiskoTextBox.Text;
            EditedUczniowie.Opis = OpisTextBox.Text;
            EditedUczniowie.Ocena = int.Parse(OcenaTextBox.Text);
            DialogResult = true;
        }
    }
}