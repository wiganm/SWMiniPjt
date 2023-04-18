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
using System.Collections.ObjectModel;
namespace WpfApp
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool startLoadButtonClicked = false;
        public ObservableCollection<PathGeometry> Lines { get; set; }

        public MainWindow()
        {

            InitializeComponent();
            Lines = new ObservableCollection<PathGeometry>();
            DrawGrid(20);

            DataContext = this;

        }
        private void DrawGrid(int gridSize)
        {
            for (int x = 0; x <= Map_.Width; x += gridSize)
            {
                var xLine = new PathGeometry();
                xLine.Figures.Add(new PathFigure(new Point(x, 0), new[] { new LineSegment(new Point(x, Map_.Height), true) }, false));
                Lines.Add(xLine);
            }

            for (int y = 0; y <= Map_.Height; y += gridSize)
            {
                var yLine = new PathGeometry();
                yLine.Figures.Add(new PathFigure(new Point(0, y), new[] { new LineSegment(new Point(Map_.Width, y), true) }, false));
                Lines.Add(yLine);
            }
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
            Point cursorPosition = e.GetPosition(Map_);

            // 위치의 X와 Y 좌표를 사용하여 작업을 수행할 수 있습니다.
            double x = cursorPosition.X;
            double y = cursorPosition.Y;


            if (!startLoadButtonClicked)
            {
                startxpos.Text = $"{x}";
                startypos.Text = $"{y}";
            }
            else
            {
                endxpos.Text = $"{x}";
                endypos.Text = $"{y}";
            }

            // 점을 그리는 코드를 추가합니다.
            int dotSize = 5; // 점의 크기
            SolidColorBrush dotColor = Brushes.Yellow; // 점의 색상

            Ellipse dot = new Ellipse
            {
                Width = dotSize,
                Height = dotSize,
                Fill = dotColor,
                Margin = new Thickness(x - (dotSize / 2), y - (dotSize / 2), 0, 0) // 점의 중심이 클릭한 위치가 되도록 조정
            };

            Map_.Children.Add(dot); // Canvas에 점 추가


        }

        private void startypos_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click1(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {

        }

        private void start_load_click(object sender, RoutedEventArgs e)
        {
            startLoadButtonClicked = true;
        }


        private void confirm_scenario_click(object sender, RoutedEventArgs e)
        {
            if (double.TryParse(startxpos.Text, out double startX) &&
                double.TryParse(startypos.Text, out double startY) &&
                double.TryParse(endxpos.Text, out double endX) &&
                double.TryParse(endypos.Text, out double endY))
            {
                // 선을 그리는 코드를 추가합니다.
                var line = new Line
                {
                    X1 = startX,
                    Y1 = startY,
                    X2 = endX,
                    Y2 = endY,
                    Stroke = Brushes.Orange,
                    StrokeThickness = 2,
                    StrokeDashArray = new DoubleCollection() { 2, 2 } // 점선을 만들기 위한 코드입니다.
                };

                Map_.Children.Add(line); // Canvas에 선 추가
            }
            else
            {
                MessageBox.Show("유효한 좌표 값을 입력하세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }


        private void end_load_click(object sender, RoutedEventArgs e)
        {

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void TextBox_TextChanged_1(object sender, TextChangedEventArgs e)
        {

        }

        private void TextBox_TextChanged_2(object sender, TextChangedEventArgs e)
        {

        }
    }
}
