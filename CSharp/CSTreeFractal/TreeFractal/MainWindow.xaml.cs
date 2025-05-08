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
using System.Windows.Threading;

namespace TreeFractal
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer Timer { get; set; }
        private Queue<Branch> Branches { get; set; } = new Queue<Branch>();
        private static readonly int MaxDepth = 8;
        private static readonly int NumberOfTrees = 3;

        public MainWindow()
        {
            InitializeComponent();

            Loaded += delegate
            {
                InititalizeTrees();
                InitializeTimer();
            };
        }

        private void InititalizeTrees()
        {
            Branch.DeltaAngle = 60.0;
            Branch.LengthRatio = 0.6;
            Console.WriteLine($"deltaAngle={Branch.DeltaAngle}");
            Console.WriteLine($"lengthRatio={Branch.LengthRatio}");

            double centerX = ActualWidth * 0.5;
            double centerY = ActualHeight * 0.5;
            double shortestSide = Math.Min(ActualWidth, ActualHeight);
            double treeAngleSeparation = 360.0 / NumberOfTrees;
            for (int t = 0; t < NumberOfTrees; t++)
            {
                double length = shortestSide * 0.2;
                double angle = -90.0 + treeAngleSeparation * t;
                Console.WriteLine($"New trunk @({centerX}, {centerY}) length={length} angle={angle}");
                Branch trunk = Branch.FromXYLA(
                    centerX,
                    centerY,
                    length,
                    angle
                );
                Branches.Enqueue(trunk);
            }
        }

        private void InitializeTimer()
        {
            Console.WriteLine("Starting animation...");
            Timer = new DispatcherTimer();
            Timer.Tick += new EventHandler(OnTick);
            Timer.Interval = new TimeSpan(0, 0, 0, 0, 10);
            Timer.Start();
        }

        private void OnTick(object sender, EventArgs e)
        {
            if (Branches.Count > 0)
            {
                Branch branch = Branches.Dequeue();
                if (branch.Depth < MaxDepth)
                {
                    Branches.Enqueue(branch.GetLeftChild());
                    Branches.Enqueue(branch.GetRightChild());
                }
                TreeCanvas.Children.Add(branch.Line);
            }
            else
            {
                Console.WriteLine("Done.");
                Timer.Stop();
            }
        }
    }
}
