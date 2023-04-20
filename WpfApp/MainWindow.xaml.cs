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
using System.Collections;


using Wrapper;

namespace WpfApp
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        GcsWrapper gcs;
        public double startposx;
        public double startposy;
        public double endposx;
        public double endposy;
        public double posx;
        public double posy;
        public double x, y;
        private string selectedValue;
        //ArrayList arrayList = new ArrayList();
        ArrayList logarrayList = new ArrayList();
        object[] scenario_array = new object[8];
        private Ellipse myEllipse = new Ellipse();
        private Ellipse myEllipse2 = new Ellipse();
        private List<Ellipse> dots = new List<Ellipse>();
        private bool endLoadButtonClicked = false;
        private bool startLoadButtonClicked = false;
        private bool posLoadButtonClicked = false;

        MediaPlayer bbyok = new MediaPlayer();

        public ObservableCollection<PathGeometry> Lines { get; set; }

        public MainWindow()
        {
            gcs = new GcsWrapper();
            InitializeComponent();
            LoadImageFromLocalFolder();
            Lines = new ObservableCollection<PathGeometry>();
            DrawGrid(20);
            gcs.UdpStart();
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
        private void RemoveElementAtCoordinate(double x, double y, double tolerance = 0.1)
        {
            List<Ellipse> elementsToRemove = new List<Ellipse>();

            foreach (UIElement element in Map_.Children)
            {
                if (element is Ellipse dot)
                {
                    double dotX = Canvas.GetLeft(dot);
                    double dotY = Canvas.GetTop(dot);

                    if (Math.Abs(dotX - x) <= tolerance && Math.Abs(dotY - y) <= tolerance)
                    {
                        elementsToRemove.Add(dot);
                    }
                }
            }

            foreach (Ellipse dot in elementsToRemove)
            {
                Map_.Children.Remove(dot);
            }
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
                if (dots.Count > 1)
                {
                    RemoveDot(dots[0]);
                    RemoveDot(dots[0]);
                }
                AddDot(dotSize, x, y, Colors.DarkBlue);
                posx = cursorPosition.X;
                posy = cursorPosition.Y;
                xpos.Text = $"{posx}";
                ypos.Text = $"{posy}";
                //arrayList.Add(posx);
                //arrayList.Add(posy);
                scenario_array[2] = posx;
                scenario_array[3] = posy;
                int scope = 100;
                AddDot(scope, x, y, Color.FromArgb(128, 135, 206, 250));

            }
            else
            {
                if (!startLoadButtonClicked)
                {
                    if (dots.Count > 2)
                    {
                        RemoveDot(dots[2]);
                    }
                    AddDot(dotSize, x, y, Colors.Yellow);
                    startposx = cursorPosition.X;
                    startposy = cursorPosition.Y;
                    startxpos.Text = $"{startposx}";
                    startypos.Text = $"{startposy}";
                    //arrayList.Add(startposx);
                    //arrayList.Add(startposy);
                    scenario_array[4] = startposx;
                    scenario_array[5] = startposy;
                    // 점을 그리는 코드를 추가합니다.

                }
                else
                {
                    if (dots.Count > 3)
                    {
                        RemoveDot(dots[3]);
                    }
                    AddDot(dotSize, x, y, Colors.Yellow);
                    endposx = cursorPosition.X;
                    endposy = cursorPosition.Y;
                    endxpos.Text = $"{endposx}";
                    endypos.Text = $"{endposy}";
                    //arrayList.Add(endposx);
                    //arrayList.Add(endposy);
                    scenario_array[6] = endposx;
                    scenario_array[7] = endposy;

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
            gcs.SendScenarioMsg((int)scenario_array[0], (double)scenario_array[1], (double)scenario_array[2], (double)scenario_array[3], (double)scenario_array[4], (double)scenario_array[5], (double)scenario_array[6], (double)scenario_array[7]);
            //gcs.SendScenarioMsg((int)arrayList[0], (double)arrayList[1], (double)arrayList[2], (double)arrayList[3], (double)arrayList[4], (double)arrayList[5], (double)arrayList[6], (double)arrayList[7]);
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

                logarrayList.Add("시나리오 배포");
                event_log.Text = logarrayList[0].ToString();
                // 여기서 시나리오 array ClassLibrary로 보내줘야해
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

        private void ShootBtn_Click(object sender, RoutedEventArgs e)
        {
            ChangeImage1();
            int dotSize = 7; // 점의 크기 설정
            logarrayList.Add("유도탄 발사");
            event_log.Text = logarrayList[0].ToString() + ", " + logarrayList[1].ToString() + ", " + logarrayList[2].ToString();
            double.TryParse(xpos.Text, out double startX);
            double.TryParse(ypos.Text, out double startY);
            double.TryParse(endxpos.Text, out double endX);
            double.TryParse(endypos.Text, out double endY);
            SolidColorBrush dotColor = Brushes.Orange; // 점의 색상을 진한 빨간색으로 설정
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
            //bbyok.Open(new Uri(@"\bbyong.mp3", UriKind.Relative));
            //bbyok.Play();
        }

        private void MyComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;

            // 선택된 ComboBoxItem을 가져옵니다.
            ComboBoxItem selectedItem = (ComboBoxItem)comboBox.SelectedItem;

            // 선택된 값을 문자열로 가져옵니다.
            selectedValue = selectedItem.Content.ToString();


        }

        private void Button_Click_5(object sender, RoutedEventArgs e)
        {

        }

        private void speed_load_click(object sender, RoutedEventArgs e)
        {
            // TextBox에서 입력된 값을 가져옵니다.
            double inputspeed;
            inputspeed = Double.Parse(speed.Text);
            //arrayList.Add(inputspeed);
            scenario_array[1] = inputspeed;

        }

        private void Button_Click_6(object sender, RoutedEventArgs e)
        {

        }

        private void simulation_start_click(object sender, RoutedEventArgs e)
        {
            gcs.Start();
            double.TryParse(startxpos.Text, out double startX);
            double.TryParse(startypos.Text, out double startY);
            double.TryParse(endxpos.Text, out double endX);
            double.TryParse(endypos.Text, out double endY);

            current_state.Text = "모의 중";
            logarrayList.Add("모의 시작");
            event_log.Text = logarrayList[0].ToString() +", " +logarrayList[1].ToString();
            current_state.Foreground = Brushes.Yellow;
            current_state.Background = Brushes.Red;
            // 진한 빨간 점 추가
            int dotSize = 7; // 점의 크기 설정

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

            // 배포 함수 사용

        }
        private void ChangeImage1()
        {
            // Specify the new image file path
            string newImagePath = @"C:\Users\User\Desktop\project\son2.png";

            // Set the image source
            var newImage = new BitmapImage();
            newImage.BeginInit();
            newImage.UriSource = new Uri(newImagePath, UriKind.Absolute);
            newImage.CacheOption = BitmapCacheOption.OnLoad;
            newImage.EndInit();

            image.Source = newImage;
        }
        private void ChangeImage2(string newImagePath)
        {
            // Specify the new image file path
            string newImagepath;
            newImagepath = newImagePath;
            //@"C:\Users\User\Desktop\project\son2.png";

            // Set the image source
            var newImage = new BitmapImage();
            newImage.BeginInit();
            newImage.UriSource = new Uri(newImagePath, UriKind.Absolute);
            newImage.CacheOption = BitmapCacheOption.OnLoad;
            newImage.EndInit();

            image.Source = newImage;
        }
        private void pos_load_click(object sender, RoutedEventArgs e)
        {
            posLoadButtonClicked = true;

        }

        private void type_select_Click(object sender, RoutedEventArgs e)
        {
            if (selectedValue == "1.탄도탄")
            { 
                speed_limit.Text = "제한속도: 1~10 마하";
                //arrayList.Add(1);
                scenario_array[0] = 1;
            }
            else if (selectedValue == "2.항공기")
            {     
                speed_limit.Text = "제한속도: 0.1~1 마하";
                //arrayList.Add(2);
                scenario_array[0] = 2;
            }
           
        }

        private void LoadImageFromLocalFolder()
        {
            string localFolderPath = @"C:\Users\User\Desktop\project";
            string imageName = "son.png";
            string imagePath = System.IO.Path.Combine(localFolderPath, imageName);

            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.UriSource = new Uri(imagePath, UriKind.Absolute);
            bitmap.EndInit();

            image.Source = bitmap;
        }
    }
}
