/*

	SampLog SQL - By GalassoX

	Version: v1.0
	
	Changelog:
		8/03/2021
			- First version.
*/

#if defined _SampLogSQL_included
	#endinput
#endif
#define _SampLogSQL_included

#include <a_samp>
#include <a_mysql>

/* 
native Log(input[]);
native Log(input[], type); // "type" works to classify logs
native ConnectDatabaseLogs(const host[], const user[], const password[], const database[]);
*/

new MySQL:gSqlConn;

stock Log(szInput[])
{
	mysql_format(gSqlConn, query, sizeof(query), "INSERT INTO `samplog`(`time`,`date`,`log`) VALUES ('%s', '%s', '%s')", time, date, szInput);
	mysql_tquery(gSqlConn, query);
}

stock LogEx(szInput[], type)
{
	mysql_format(gSqlConn, query, sizeof(query), "INSERT INTO `samplog`(`time`,`date`,`log`,`type`) VALUES ('%s', '%s', '%s','%i')", time, date, szInput, option);
	mysql_tquery(gSqlConn, query);
}

stock ConnectDatabaseLogs(const host[], const user[], const password[], const database[])
{
	gSqlConn = mysql_connect(host, user, password, database);	
	if (mysql_errno() != 0)
	{
	    switch (mysql_errno())
	    {
			case 1045: printf("[SAMPLOG-SQL] ERROR: Access denied!\n User: %s\n Password: %s", MYSQL_USER, MYSQL_PASSWORD);
			case 1049: printf("[SAMPLOG-SQL] ERROR: Unknow database\n Database: %s", MYSQL_DATABASE);
			case 2005: printf("[SAMPLOG-SQL] ERROR: Failed to connect to host\n Host: %s", MYSQL_HOST);
			default: printf("[SAMPLOG-SQL] ERROR: Could not connect to the database, error %d", mysql_errno());
	    }
	}
	else print("[SAMPLOG-SQL] -> Connection with database sucess!");

	mysql_tquery(gSqlConn, "CREATE TABLE IF NOT EXISTS `samplog` (`time` varchar(10) NOT NULL DEFAULT '',`date` varchar(10) NOT NULL DEFAULT '',`log` varchar(256) NOT NULL DEFAULT '',`type` int(11) NOT NULL DEFAULT '')");
	return 1;
}