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
using System.Windows.Threading;
namespace WpfApp
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public double startposx;
        public double startposy;
        public double endposx;
        public double endposy;
        public double posx;
        public double posy;
        public double x, y;
        int[][] scenario = new int[8][];
        //posArray[0] = new int[2];
        //posArray[1] = new int[2];
        //posArray[2] = new int[2];
        private List<Ellipse> dots = new List<Ellipse>();
        private bool endLoadButtonClicked = false;
        private bool startLoadButtonClicked = false;
        private bool posLoadButtonClicked = false;
        
        public ObservableCollection<PathGeometry> Lines { get; set; }

        public MainWindow()
        {

            InitializeComponent();
            Lines = new ObservableCollection<PathGeometry>();
            DrawGrid(20);

            DataContext = this;

        }
        
        // 진한 빨간 점 이동 메소드 추가
        private async void MoveDot(Ellipse dot, double startX, double startY, double endX, double endY, TimeSpan duration)
        {
            double distanceX = endX - startX; // X축 이동 거리 계산
            double distanceY = endY - startY; // Y축 이동 거리 계산
            int steps = 20; // 이동을 나눌 단계 설정
            double stepX = distanceX / steps; // 각 단계에서 X축 이동 거리 계산
            double stepY = distanceY / steps; // 각 단계에서 Y축 이동 거리 계산
            int dotSize = 5;

            for (int i = 0; i < steps; i++) // 각 단계별로 이동
            {
                double newX = startX + (stepX * i); // 새로운 X 좌표 계산
                double newY = startY + (stepY * i); // 새로운 Y 좌표 계산
                dot.Margin = new Thickness(newX - (dotSize / 2), newY - (dotSize / 2), 0, 0); // 점 위치 업데이트

                await Task.Delay(duration); // 지정한 시간만큼 대기
            }

            dot.Margin = new Thickness(endX - (dotSize / 2), endY - (dotSize / 2), 0, 0); // 점의 최종 위치 설정
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
        private Ellipse AddDot(int dotSize, double x, double y, Color color)
        {
            SolidColorBrush dotColor = new SolidColorBrush(color);

            Ellipse dot = new Ellipse
            {
                Width = dotSize,
                Height = dotSize,
                Fill = dotColor,
                Margin = new Thickness(x - (dotSize / 2), y - (dotSize / 2), 0, 0)
            };

            // 점을 List에 추가
            dots.Add(dot);

            Map_.Children.Add(dot);

            return dot;
        }

        private void RemoveDot(Ellipse dot)
        {
            if (dots.Contains(dot))
            {
                Map_.Children.Remove(dot);
                dots.Remove(dot);
            }
        }
        private void Map_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            // Canvas에서 커서의 현재 위치를 가져옵니다.
            
            Point cursorPosition = e.GetPosition(Map_);

           
            // 위치의 X와 Y 좌표를 사용하여 작업을 수행할 수 있습니다.

            int dotSize = 5; // 점의 크기

            x = cursorPosition.X;
            y = cursorPosition.Y;

            if (!posLoadButtonClicked)
            {

                AddDot(dotSize, x, y, Colors.DarkBlue);
                posx = cursorPosition.X;
                posy = cursorPosition.Y;
                xpos.Text = $"{posx}";
                ypos.Text = $"{posy}";
                int scope = 100;
                AddDot(scope, x, y, Color.FromArgb(128, 135, 206, 250));

            }
            else
            {
                if (!startLoadButtonClicked)
                {
                    AddDot(dotSize, x, y, Colors.Yellow);
                    startposx = cursorPosition.X;
                    startposy = cursorPosition.Y;
                    startxpos.Text = $"{startposx}";
                    startypos.Text = $"{startposy}";
                    // 점을 그리는 코드를 추가합니다.

                }
                else
                {
                    AddDot(dotSize, x, y, Colors.Yellow);
                    endposx = cursorPosition.X;
                    endposy = cursorPosition.Y;
                    endxpos.Text = $"{endposx}";
                    endypos.Text = $"{endposy}";

                }
            }
    




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
            startxpos.Text = $"{x}";
            startypos.Text = $"{y}";
        }
        private void end_load_click(object sender, RoutedEventArgs e)
        {
            endLoadButtonClicked = true;
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

                // 진한 빨간 점 추가
                int dotSize = 5; // 점의 크기 설정
                SolidColorBrush dotColor = Brushes.DarkRed; // 점의 색상을 진한 빨간색으로 설정
                Ellipse redDot = new Ellipse // 새로운 원형 도형(점) 생성
                {
                    Width = dotSize,
                    Height = dotSize,
                    Fill = dotColor,
                    Margin = new Thickness(startX - (dotSize / 2), startY - (dotSize / 2), 0, 0) // 점의 중심이 시작 좌표가 되도록 위치 조정
                };
                Map_.Children.Add(redDot); // Canvas에 점 추가

                // 진한 빨간 점 이동
                TimeSpan duration = TimeSpan.FromMilliseconds(500);
                MoveDot(redDot, startX, startY, endX, endY, duration);
            }
            else
            {
                MessageBox.Show("유효한 좌표 값을 입력하세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
            }
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

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {

        }

        private void pos_load_click(object sender, RoutedEventArgs e)
        {
            posLoadButtonClicked = true;
           
        }
    }
}
