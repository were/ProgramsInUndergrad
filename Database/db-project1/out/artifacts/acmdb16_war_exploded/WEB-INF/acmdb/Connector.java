package acmdb;

import java.sql.*;

public class Connector {
    public Connection con;
    public Statement stmt;
    public Connector() throws Exception {
        try {
            String userName = "root";
            String password = "000000";
            String url = "jdbc:mysql://localhost/acmdb";
            Class.forName ("com.mysql.jdbc.Driver").newInstance ();
            con = DriverManager.getConnection (url, userName, password);

            //DriverManager.registerDriver (new oracle.jdbc.driver.OracleDriver());
            //stmt=con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            stmt = con.createStatement();
            //stmt=con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
        }
        catch(Exception e) {
            System.err.println("Unable to open mysql jdbc connection. The error is as follows,\n");
            System.err.println(e.getMessage());
            throw(e);
        }
    }

    public void closeStatement() throws Exception{
        stmt.close();
    }

    public void closeConnection() throws Exception{
        con.close();
    }
}

