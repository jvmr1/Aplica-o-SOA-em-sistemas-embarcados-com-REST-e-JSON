/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Connection;

import java.sql.*;

/**
 *
 * @author higos
 */
public class DAO {
    private static final String banco = "jdbc:derby:" 
           +"C:/Users/jvmr1/Documents/NetBeansProjects/ServerREST/RESTBD";
    private static final String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    private static final String usuario = "rest";
    private static final String senha = "123";
    private static Connection con = null;

    public static Connection getConexao() {
        if (con == null) {
            try {
                Class.forName(driver);
                con = DriverManager.getConnection(banco, usuario, senha);
            } catch (ClassNotFoundException ex) {
                System.out.println("Não encontrou o driver");
            } catch (SQLException ex) {
                System.out.println("Erro ao conectar: "
                        + ex.getMessage());
            }
        }
        return con;
    }

    public static PreparedStatement getPreparedStatement(String sql) {
        if (con == null) {
            con = getConexao();
        }
        try {
            return con.prepareStatement(sql);
        } catch (SQLException e) {
            System.out.println("Erro de sql: "
                    + e.getMessage());
        }
        return null;
    }

}
