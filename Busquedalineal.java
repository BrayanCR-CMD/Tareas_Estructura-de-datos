import java.util.Scanner;

public class Busquedalineal{

    public static int busqueda(String [] Nombres, String buscar, int largo){
    for (int i=0; i < largo; i++){
        if (Nombres[i].equals(buscar)){
            return i;
        }
    }
    return -1;
}

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String [] Nombres = new String[5];
        String buscar;
        int largo = Nombres.length;
        for (int i=0; i < Nombres.length; i++){
            System.out.println("ingrese el nombre");
            Nombres[i] = sc.nextLine();
        }
        System.out.println("ingrese un nombre que dese buscar");
        buscar = sc.nextLine();

        if (busqueda(Nombres, buscar, largo) == -1){
            System.out.println("el nombre no se encontro");
        }else{
            System.out.println("el nombre se encuentra en la posicion" + busqueda(Nombres, buscar, largo));
        }
    }
}