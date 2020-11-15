/*
Modificare il programma XMLWriter in modo da modellare e salvare su file 

COMPITO:

Complichiamo un po' le cose e modelliamo una lista di automobili


class Car {
	String color;
	String plateN;
	Person owner;
	Public Car(String color, String plateN, Person owner) {…}
}

ArrayList<Car> garage = new ArrayList<>();
Person person1 = new Person("Francesco", 47);
Car car1 = new Car("grey", "102021", person1);
Person person2= new Person("Aurora", 41);
Car car2 = new Car("red", "21313", person2);

garage.add(car1);
garage.add(car2);

HINT:
<garage>
    <car ...>
        <owner ... ></owner>
    </car>
    <car ...>
        <owner ...></owner>
    </car>
</garage>
 */
package xml;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import java.io.File;
import java.util.ArrayList;

public class XMLWriter {
    public static void writeXML(ArrayList<Car> cars, String filename) {
        try {
            // CREO IL DOCUMENTO XML
            DocumentBuilderFactory documentFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder documentBuilder = documentFactory.newDocumentBuilder();
            Document document = documentBuilder.newDocument();

            // RIEMPIAMO IL DOCUMENTO
            // Create root element (garage)
            Element root = document.createElement("garage");
            
            // add root to the document
            document.appendChild(root);

            // add a car elemtn for every car object
            for (Car car_number : cars) {
                Element car = document.createElement("car");
                
                // Create attribute of car
                car.setAttribute("plateNumber", "" + car_number.plateN);
                car.setAttribute("color", "" + car_number.color);
                
                // add it to root
                root.appendChild(car);

                // Create owner (person) element
                Element owner = document.createElement("owner");

                // Create attribute of person
                owner.setAttribute("owner", "" + car_number.owner.getName());
                owner.setAttribute("age", "" + car_number.owner.getAge());

                // add owner element in car element 
                car.appendChild(owner);
            }

            // OUTPUT
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource domSource = new DOMSource(document);
            StreamResult streamResult = new StreamResult(new File(filename));
            transformer.transform(domSource, streamResult);

        } catch (Exception ex) {}
    }

    public static void main(String[] args) {
        //arrayList
        ArrayList<Person> persons = new ArrayList<>();
        ArrayList<Car> garage = new ArrayList<>();

        //creation of a person
        Person person1 = new Person("Francesco", 47);
        Person person2 = new Person("Aurora", 41);

        //creation of a car with the info of the owner
        Car car1 = new Car("grey", "102021", person1);
        Car car2 = new Car("red", "21313", person2);

        //add the info of person in an arraylist persons
        persons.add(person1);
        persons.add(person2);

        //add car info in the arraylist garage
        garage.add(car1);
        garage.add(car2);

        writeXML(garage, "cars.xml");
    }
}
