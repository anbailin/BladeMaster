using System;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using Extensibility;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.CommandBars;
using System.Resources;
using System.Reflection;
using System.Globalization;
using System.Diagnostics;
using Microsoft.VisualStudio.VCProjectEngine;
using System.Text.RegularExpressions;

namespace UnityBuild
{
    internal class Cpp
    {
        public string Name;
        public string Condition = "";
        public Unity Unity;
        public string VirtualPath = "";
        public long Size;

        public string UnityName
        {
            get { return (this.Unity == null ? "" : this.Unity.Name); }
        }

        public Cpp(string name)
        {
            this.Name = name;
        }

        public Cpp(VCFile file)
        {
            this.Name = file.RelativePath;
            this.VirtualPath = Connect.GetVirtualPath(file);
            this.Size = Utils.GetFileSize(file.FullPath);
        }
    }
}
