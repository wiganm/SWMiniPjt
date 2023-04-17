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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void InputTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            var textBox = sender as TextBox;

            // 입력된 텍스트를 double 형식으로 변환하려고 시도합니다.
            if (double.TryParse(textBox.Text, out double result))
            {
                // 변환에 성공하면 텍스트 박스의 테두리를 기본 색으로 변경합니다.
                textBox.BorderBrush = (Brush)new BrushConverter().ConvertFromString("#FFABADB3");
            }
            else
            {
                // 변환에 실패하면 텍스트 박스의 테두리를 빨간색으로 변경하여 유효하지 않은 입력임을 나타냅니다.
                textBox.BorderBrush = Brushes.Red;
            }
        }



 

        private void endxpos_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void startxpos_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void Map_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            // Canvas에서 커서의 현재 위치를 가져옵니다.
            Point cursorPosition = e.GetPosition(Map);

            // 위치의 X와 Y 좌표를 사용하여 작업을 수행할 수 있습니다.
            double x = cursorPosition.X;
            double y = cursorPosition.Y;

            // 예를 들어, 좌표를 출력합니다.
            Console.WriteLine($"Cursor coordinates: X={x}, Y={y}");
            startxpos.Text = $"{x}";
            startypos.Text = $"{y}";
        }

        private void startypos_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }
    }
}
