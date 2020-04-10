/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Metodos;

import Connection.GerenciarDAO;
import Connection.Temperatura;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;

/**
 *
 * @author higos
 */

@Path("postTemperatura")

public class PostTemperatura {

 
    @POST
    @Consumes("text/json")   
    public String setName(String content) {
        try{
        Gson g = new Gson();
        Temperatura s = g.fromJson(content, Temperatura.class);
        if(s.getSensornumero() != null && s.getTemperatura() != null){
            GerenciarDAO gd = new GerenciarDAO();
            gd.updateTemperatura(s.getTemperatura(), s.getSensornumero());
            
            
            return "JSON válido, Temperatura: " + s.getTemperatura() + " registrada para o sensor: " + s.getSensornumero();
        } else {
            return "JSON inválido | Padrão exemplo: {\"temperatura\":\"38.94\",\"sensornumero\":\"1\"}";
        }
         }catch(JsonSyntaxException e){
            return "Não é um JSON | Padrão exemplo: {\"temperatura\":\"38.94\",\"sensornumero\":\"1\"}";
        }

    }

}
