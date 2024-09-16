using System;
using System.Collections.ObjectModel;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Dziennik
{
    public partial class MainWindow : Window
    {
        public ObservableCollection<Uczen> Uczniowie { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            Uczniowie = new ObservableCollection<Uczen>();
            UczniowieDataGrid.DataContext = this;
        }
      

        private void AddUczen_Click(object sender, RoutedEventArgs e)
        {
            var addUczenWindow = new DodajUcznia();
            if (addUczenWindow.ShowDialog() == true)
            {
                Uczniowie.Add(addUczenWindow.NewUczen);
            }
        }

        private void EditUczen_Click(object sender, RoutedEventArgs e)
        {
            if (UczniowieDataGrid.SelectedItem is Uczen selectedUczen)
            {
                var editUczenWindow = new EdytujUcznia(selectedUczen);
                if (editUczenWindow.ShowDialog() == true)
                {
                    int index = Uczniowie.IndexOf(selectedUczen);
                    Uczniowie[index] = editUczenWindow.EditedUczniowie;
                    UczniowieDataGrid.Items.Refresh();
                }

            }
        }

        private void DeleteUczen_Click(object sender, RoutedEventArgs e)
        {
            if (UczniowieDataGrid.SelectedItem is Uczen selectedUczen)
            {
                Uczniowie.Remove(selectedUczen);
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void About_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Dziennik\nVersion 1.0", "About");
        }
    }
}