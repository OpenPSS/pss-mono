//
// System.Diagnostics.EventLogPermissionAccess.cs
//
// Authors:
//	Jonathan Pryor (jonpryor@vt.edu)
//	Sebastien Pouliot  <sebastien@ximian.com>
//
// (C) 2002 Jonathan Pryor
// Copyright (C) 2004 Novell, Inc (http://www.novell.com)
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
namespace System.Diagnostics {

	[Flags]
#if !NET_2_0
	[Serializable]
#endif
	public enum EventLogPermissionAccess {
		None=0,
#if NET_2_0
		[Obsolete ()]
		Browse=0x2,
		[Obsolete ()]
		Instrument=0x6,
		[Obsolete ()]
		Audit=0xA,
		Write = 16,
		Administer = 48,
#else
		Browse=0x2,
		Instrument=0x6,
		Audit=0xA,
#endif
	}
}

#endif
