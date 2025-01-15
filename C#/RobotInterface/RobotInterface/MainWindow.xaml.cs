using System.IO.Ports;
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
using ExtendedSerialPort_NS;

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        string receivedText; 

        public MainWindow()
        {
            //InitializeComponent();
            //serialPort1 = new ExtendedSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            //serialPort1.Open();
            serialPort1 = new ExtendedSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();


        }
        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {

            TextBoxReception.Text += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);


        }




        private void ButtonEnvoyer_Click_1(object sender, RoutedEventArgs e)
        {

            if (ButtonEnvoyer.Background == Brushes.RoyalBlue)
            {
                ButtonEnvoyer.Background = Brushes.Beige;
            }
            else
            {
                ButtonEnvoyer.Background = Brushes.RoyalBlue;
            }
            SendMessage();
            
        }

        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                if (ButtonEnvoyer.Background == Brushes.RoyalBlue)
                {
                    ButtonEnvoyer.Background = Brushes.Beige;
                }
                else
                {
                    ButtonEnvoyer.Background = Brushes.RoyalBlue;
                }
                SendMessage();
            }

        }
        private void SendMessage()
        {
            //TextBoxReception.Text += "Recu: " + TextBoxEmission.Text + Environment.NewLine;
            
            serialPort1.WriteLine(TextBoxEmission.Text);
            //TextBoxEmission.Clear();

        }
    }
}