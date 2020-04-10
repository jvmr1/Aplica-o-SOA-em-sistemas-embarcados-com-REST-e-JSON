package Metodos;

import Connection.GerenciarDAO;
import com.google.gson.Gson;
import javax.ws.rs.Path;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;

/**
 * REST Web Service
 *
 * @author higos
 */

@Path("getTemperatura")
public class GetTemperatura {

    @GET
    @Produces("application/json")
    public String getGreeting() {
        GerenciarDAO gd = new GerenciarDAO();
        Gson g = new Gson();
        return g.toJson(gd.getTemperatura());

    }

}
