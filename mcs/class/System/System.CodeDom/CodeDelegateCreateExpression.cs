//
// System.CodeDom CodeDelegateCreateExpression Class implementation
//
// Author:
//   Miguel de Icaza (miguel@ximian.com)
//   Daniel Stodden (stodden@in.tum.de)
//
// (C) 2001 Ximian, Inc.
// Copyright (C) 2005 Novell, Inc (http://www.novell.com)
//
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

#if !MOBILE
using System.Runtime.InteropServices;

namespace System.CodeDom 
{
	[Serializable]
	[ClassInterface(ClassInterfaceType.AutoDispatch)]
	[ComVisible(true)]
	public class CodeDelegateCreateExpression
		: CodeExpression 
	{
		private CodeTypeReference delegateType;
		private string methodName;
		private CodeExpression targetObject;

		//
		// Constructors
		//
		public CodeDelegateCreateExpression ()
		{
		}

		public CodeDelegateCreateExpression (CodeTypeReference delegateType,
						     CodeExpression targetObject,
						     string methodName)
		{
			this.delegateType = delegateType;
			this.targetObject = targetObject;
			this.methodName = methodName;
		}


		//
		// Properties
		//
		public CodeTypeReference DelegateType {
			get {
				if (delegateType == null) {
					delegateType = new CodeTypeReference (string.Empty);
				}
				return delegateType;
			}
			set {
				delegateType = value;
			}
		}

		public string MethodName {
			get {
				if (methodName == null) {
					return string.Empty;
				}
				return methodName;
			}
			set {
				methodName = value;
			}
		}

		public CodeExpression TargetObject {
			get {
				return targetObject;
			}
			set {
				targetObject = value;
			}
		}

		//
		// ICodeDomVisitor method
		//
		internal override void Accept (ICodeDomVisitor visitor)
		{
			visitor.Visit (this);
		}
	}
}
#endif
