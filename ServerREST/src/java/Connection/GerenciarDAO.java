package Connection;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author higos
 */
public class GerenciarDAO {

    public ArrayList getSensor() {
        ArrayList<Sensor> sensor = new ArrayList<Sensor>();
        String sql = "SELECT * FROM sensor";
        PreparedStatement pst = DAO.getPreparedStatement(sql);
        ResultSet rs;
        try {
            rs = pst.executeQuery();

            while (rs.next()) {
                Sensor s = new Sensor();
                s.setData(rs.getString("data"));
                s.setHoras(rs.getString("horas"));
                s.setSensornumero(rs.getString("sensornumero"));
                sensor.add(s);
            }
            pst.close();
        } catch (SQLException ex) {
            Logger.getLogger(GerenciarDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
        return sensor;

    }

    public ArrayList getTemperatura() {
        ArrayList<Temperatura> temp = new ArrayList<Temperatura>();
        String sql = "SELECT * FROM temperatura";
        PreparedStatement pst = DAO.getPreparedStatement(sql);
        ResultSet rs;
        try {
            rs = pst.executeQuery();

            while (rs.next()) {
                Temperatura t = new Temperatura();
                t.setTemperatura(rs.getString("temperatura"));
                t.setData(rs.getString("data"));
                t.setHora(rs.getString("horas"));
                t.setSensornumero(rs.getString("sensornumero"));
                temp.add(t);
            }
            pst.close();
        } catch (SQLException ex) {
            Logger.getLogger(GerenciarDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
        return temp;
    }

    public boolean updatePresenca(String sensor) {
        String sql = "insert into sensor (sensornumero, data, horas)"
                + " values (?,CURRENT_DATE,CURRENT_TIME)";
        Boolean retorno = false;
        System.out.print("Update Presença");
        PreparedStatement pst = DAO.getPreparedStatement(sql);
        try {
            pst.setString(1, sensor);
            if (pst.executeUpdate() > 0) {
                retorno = true;
            }
        } catch (SQLException ex) {
            Logger.getLogger(GerenciarDAO.class.getName()).log(Level.SEVERE, null, ex);
            retorno = false;
        }
        return retorno;
    }

    public boolean updateTemperatura(String temp, String sensor) {
        String sql = "insert into temperatura (temperatura, sensornumero, horas, data) values (?,?, CURRENT_TIME,CURRENT_DATE)";
        Boolean retorno = false;
        PreparedStatement pst = DAO.getPreparedStatement(sql);

        try {
            pst.setString(1, temp);
            pst.setString(2, sensor);
            if (pst.executeUpdate() > 0) {
                retorno = true;
            }
        } catch (SQLException ex) {
            Logger.getLogger(GerenciarDAO.class.getName()).log(Level.SEVERE, null, ex);
            retorno = false;
        }
        System.out.print("Update Temperatura: " + temp);
        return retorno;
    }
}
