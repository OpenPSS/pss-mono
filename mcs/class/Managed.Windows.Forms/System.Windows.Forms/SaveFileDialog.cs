// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Copyright (c) 2005 Novell, Inc. (http://www.novell.com)
//
// Authors:
//
//  Alexander Olk	xenomorph2@onlinehome.de
//

// NOT COMPLETE - work in progress

using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;

namespace System.Windows.Forms {
	[Designer ("System.Windows.Forms.Design.SaveFileDialogDesigner, " + Consts.AssemblySystem_Design, "System.ComponentModel.Design.IDesigner")]
	public sealed class SaveFileDialog : FileDialog {
		#region Public Constructors
		public SaveFileDialog ()
		{
			form.SuspendLayout ();
			
			form.Text = "Save";
			
			OpenSaveButtonText = "Save";
			SearchSaveLabel = "Save in:";
			fileDialogType = FileDialogType.SaveFileDialog;
			
			form.ResumeLayout (false);
		}
		#endregion	// Public Constructors
		
		#region Public Instance Properties
		[DefaultValue(false)]
		public new bool CreatePrompt {
			set {
				createPrompt = value;
			}
			
			get {
				return createPrompt;
			}
		}
		
		[DefaultValue(true)]
		public new bool OverwritePrompt {
			set {
				overwritePrompt = value;
			}
			
			get {
				return overwritePrompt;
			}
		}
		#endregion	// Public Instance Properties
		
		#region Public Instance Methods
		public Stream OpenFile ()
		{
			if (FileName == null)
				throw new ArgumentNullException ("OpenFile", "FileName is null");
			
			Stream retValue;
			
			try {
				retValue = new FileStream (FileName, FileMode.Create, FileAccess.ReadWrite);
			} catch (Exception) {
				retValue = null;
			}
			
			return retValue;
		}
		#endregion	// Public Instance Methods
		
		public override void Reset ()
		{
			base.Reset ();
			overwritePrompt = true;
			createPrompt = false;
		}
	}
}

