using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OMDemo1
{
    static class VentStateMachine
    {
        public enum BreathStates { None, PreVentilation, Inhalation, Exhalation, TimingPause };
        public enum GasStates { NoGas, O2Filling, AirFIlling };

        private static long millisStart = 0;
        private static long millisToRun = 0;

        public static void StateMachine()
        {
            //if (GlobalVars.BreathState == BreathStates.PreVentilation)
            //{
            switch (GlobalVars.BreathState)
            {
                case BreathStates.None:
                    ToPreVentilation();
                    break;

                case BreathStates.PreVentilation:
                    if (!DoPreVentilation())
                    {
                        ToInhalation();
                    }
                    break;

                case BreathStates.Inhalation:
                    if (!DoInhalation())
                    {
                        ToExhalation();
                    }
                    break;

                case BreathStates.Exhalation:
                    if (!DoExhalation())
                    {
                        ToTimingPause();
                    }
                    break;

                case BreathStates.TimingPause:
                    if (!DoTimingPause())
                    {
                        ToInhalation();
                    }
                    break;

                default:
                    throw new System.Exception("Somehow we're in an unexpected state in breath cycle");
                }
            //}
        }

        private static long GetMillis()
        {
            return DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
        }

        private static bool DoTimedState()
        {
            if (GetMillis() < millisStart + millisToRun)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static void ToPreVentilation()
        {
            GlobalVars.gValves.Clear();
            GlobalVars.gValves.SetValves(false, false, true, false);
            millisStart = GetMillis();
            millisToRun = 3000;
            GlobalVars.BreathState = BreathStates.PreVentilation;
        }

        public static bool DoPreVentilation()
        {
            return DoTimedState();
        }

        public static void ToInhalation()
        {
            GlobalVars.gValves.Clear();
            GlobalVars.gValves.SetValves(false, true, false, false);
            millisStart = GetMillis();
            millisToRun = 3000;
            GlobalVars.BreathState = BreathStates.Inhalation;
        }

        public static bool DoInhalation()
        {
            return DoTimedState();
        }

        public static void ToExhalation()
        {
            GlobalVars.gValves.Clear();
            GlobalVars.gValves.SetValves(false, true, true, false);
            millisStart = GetMillis();
            millisToRun = 3000;
            GlobalVars.BreathState = BreathStates.Exhalation;
        }

        public static bool DoExhalation()
        {
            return DoTimedState();
        }

        public static void ToTimingPause()
        {
            GlobalVars.gValves.Clear();
            GlobalVars.gValves.SetValves(true, false, false, false);
            millisStart = GetMillis();
            millisToRun = 3000;
            GlobalVars.BreathState = BreathStates.TimingPause;
        }

        public static bool DoTimingPause()
        {
            return DoTimedState();
        }

        public static void ToFillO2()
        {
        }

        public static bool DoFillO2()
        {
            return DoTimedState();
        }

        public static void ToFillAir()
        {
           
        }

        public static bool DoFillAir()
        {
            return DoTimedState();
        }

    }
}
