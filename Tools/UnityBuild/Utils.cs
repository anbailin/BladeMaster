using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Text.RegularExpressions;

namespace UnityBuild
{
    internal static class Utils
    {
        public static Regex IncludeRegex = new Regex("[ \t]*#[ \t]*include[ \t]*[\"](?<Include>[^\">]*)[\"]", RegexOptions.Compiled | RegexOptions.Singleline | RegexOptions.ExplicitCapture);

        public static string ReadAllText(string filename)
        {
            using (StreamReader reader = new StreamReader(filename))
            {
                return reader.ReadToEnd();
            }
        }

        public static void WriteAllText(string filename, string text)
        {
            if (File.Exists(filename))
            {
                FileInfo info = new FileInfo(filename);
                info.IsReadOnly = false;
            }
            File.WriteAllText(filename, text);
        }

        public static bool CompareText(string filename, string text)
        {
            if (!File.Exists(filename)) return false;
            return text == ReadAllText(filename);
        }

        public static string NormalizePath(string path)
        {
            return path.Replace('\\', '/');
        }

        public static long GetFileSize(string filename)
        {
            if (File.Exists(filename))
            {
                FileInfo info = new FileInfo(filename);
                return info.Length;
            }
            return 0;
        }

        public static string GetDirectoryPath(string filename)
        {
            if (File.Exists(filename))
            {
                FileInfo info = new FileInfo(filename);
                return info.DirectoryName;
            }
            return "";
        }

        public static void ShowError(string format, params object[] args)
        {
            string message = String.Format(format, args);
            MessageBox.Show(message, "Unity Build", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static void ShowWarning(string format, params object[] args)
        {
            string message = String.Format(format, args);
            MessageBox.Show(message, "Unity Build", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        public static void ShowMessage(string format, params object[] args)
        {
            string message = String.Format(format, args);
            MessageBox.Show(message, "Unity Build", MessageBoxButtons.OK, MessageBoxIcon.None);
        }

        public static string AddPrefixToFileName(string filename, string prefix)
        {
            return Path.Combine(Path.GetDirectoryName(filename), prefix + Path.GetFileNameWithoutExtension(filename) + Path.GetExtension(filename));
        }

        public static string AddSuffixToFileName(string filename, string suffix)
        {
            return Path.Combine(Path.GetDirectoryName(filename), Path.GetFileNameWithoutExtension(filename) + suffix + Path.GetExtension(filename));
        }

        public static XmlElement AddXmlElement(XmlNode xParent, string name)
        {
            XmlDocument xDoc = xParent.OwnerDocument;
            if (xParent is XmlDocument)
            {
                xDoc = xParent as XmlDocument;
            }

            XmlElement e = xDoc.CreateElement(name);
            xParent.AppendChild(e);
            return e;
        }

        public static XmlAttribute AddXmlAttribute(XmlNode xParent, string name, string value)
        {
            XmlAttribute a = xParent.OwnerDocument.CreateAttribute(name);
            a.Value = value;
            xParent.Attributes.Append(a);
            return a;
        }
    }

    internal class Singleton<T> where T : class, new()
    {
        public static T Instance { get { return Creator.Instance; } }

        private static class Creator
        {
            public static readonly T Instance = new T();
        }
    }
}
