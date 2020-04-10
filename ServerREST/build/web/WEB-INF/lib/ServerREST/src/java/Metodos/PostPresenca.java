/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Metodos;

import Connection.GerenciarDAO;
import Connection.Sensor;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;

/**
 *
 * @author higos
 */

@Path("postPresenca")

public class PostPresenca {

  
    @POST
    @Consumes("text/json")

    public String setName(String content) {
        try {
            Gson g = new Gson();
            Sensor s = g.fromJson(content, Sensor.class);
            if (s.getSensornumero() == null) {
                return "JSON inválido | Padrão exemplo: {\"sensornumero\":\"1\"}";
            } else {
                GerenciarDAO gd = new GerenciarDAO();
                gd.updatePresenca(s.getSensornumero());
                return "É um JSON válido, movimento registrado para o sensor: " + s.getSensornumero();
            }

        } catch (JsonSyntaxException e) {
            return "Não é um JSON | Padrão exemplo: {\"sensornumero\":\"1\"}";
        }

    }

}
