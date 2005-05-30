/* 
 * @(#)SqlErrorCollection.java	1.0 01/01/03
 *
 * Copyright 2002 Mainsoft Corporation. All Rights Reserved.
 *
 * This software is the proprietary information of Mainsoft Corporation.
 * Use is subject to license terms.
 *
 */

namespace System.Data.SqlClient
{

    /**
     * Collects all errors generated by the SQL .NET Data Provider.
     *
     * @author  Pavel Sandler
     * @version 1.0, 01/01/03
     */

    using System.Collections;
	using System.Data.Common;
	using System.Data.ProviderBase;
	using java.sql;


	[Serializable]
    public class SqlErrorCollection : AbstractDbErrorCollection
    {
		internal SqlErrorCollection(SQLException e, AbstractDBConnection connection) : base(e, connection) {}
        /**
         * Gets the error at the specified index.
         *
         * @param index of the error
         * @return Error on specified index
         */
        public SqlError this[int index]
        {
            get
            {
                return (SqlError)GetDbItem(index);
            }
        }

		protected override AbstractDbError CreateDbError(java.sql.SQLException e, System.Data.Common.AbstractDBConnection connection) {
			return new SqlError(e, connection);
		}

        
    }
}