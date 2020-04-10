/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Metodos;

import Connection.GerenciarDAO;
import com.google.gson.Gson;
import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.ws.rs.Produces;
import javax.ws.rs.GET;
import javax.ws.rs.Path;

/**
 * REST Web Service
 *
 * @author higo
 */

@Path("getSensor")
public class GetSensor {

    @GET
    @Produces("application/json")
    public String getGreeting() {
        GerenciarDAO gd = new GerenciarDAO();
        Gson g = new Gson();
        return g.toJson(gd.getSensor());

    }
}
