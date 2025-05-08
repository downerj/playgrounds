using System;
using System.Windows.Media;
using System.Windows.Shapes;

namespace TreeFractal
{
    class Branch
    {
        public static double LengthRatio { get; set; } = 0.5;
        public static double DeltaAngle { get; set; } = 45.0;

        public double X1 { get; private set; }
        public double Y1 { get; private set; }
        public double X2 { get; private set; }
        public double Y2 { get; private set; }
        public double Length { get; private set; }
        public double Angle { get; private set; }
        public double Depth { get; private set; } = 0;
        public Line Line { get; private set; }
        private Branch LeftChild { get; set; } = null;
        private Branch RightChild { get; set; } = null;

        public static double DegreesToRadians(double degrees)
        {
            return degrees * Math.PI / 180.0;
        }

        public static double RadiansToDegrees(double radians)
        {
            return radians * 180.0 / Math.PI;
        }

        public static Branch FromXYXY(double x1, double y1, double x2, double y2)
        {
            double dx = x2 - x1;
            double dy = y2 - y1;

            return new Branch
            {
                X1 = x1,
                Y1 = y1,
                X2 = x2,
                Y2 = y2,
                Length = Math.Sqrt(dx * dx + dy * dy),
                Angle = RadiansToDegrees(Math.Atan2(dy, dx)),
                Line = new Line
                {
                    X1 = x1,
                    Y1 = y1,
                    X2 = x2,
                    Y2 = y2,
                    Stroke = Brushes.Red,
                    StrokeThickness = 2
                }
            };
        }

        public static Branch FromXYLA(double x, double y, double length, double angle)
        {
            double radians = DegreesToRadians(angle);
            double cosA = Math.Cos(radians);
            double sinA = Math.Sin(radians);
            double x2 = x + length * cosA;
            double y2 = y + length * sinA;

            return new Branch
            {
                X1 = x,
                Y1 = y,
                X2 = x2,
                Y2 = y2,
                Length = length,
                Angle = angle,
                Line = new Line
                {
                    X1 = x,
                    Y1 = y,
                    X2 = x2,
                    Y2 = y2,
                    Stroke = Brushes.Red,
                    StrokeThickness = 2
                }
            };
        }

        public Branch GetLeftChild()
        {
            if (LeftChild != null)
            {
                return LeftChild;
            }

            LeftChild = FromXYLA(X2, Y2, Length * LengthRatio, Angle + DeltaAngle);
            LeftChild.Depth = Depth + 1;
            return LeftChild;
        }

        public Branch GetRightChild()
        {
            if (RightChild != null)
            {
                return RightChild;
            }

            RightChild = FromXYLA(X2, Y2, Length * LengthRatio, Angle - DeltaAngle);
            RightChild.Depth = Depth + 1;
            return RightChild;
        }
    }
}
