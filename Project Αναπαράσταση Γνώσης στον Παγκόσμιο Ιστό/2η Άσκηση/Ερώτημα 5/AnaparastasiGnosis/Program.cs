using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using VDS.RDF;
using VDS.RDF.Parsing;
using VDS.RDF.Query;
using VDS.RDF.Query.Datasets;
using VDS.RDF.Query.Inference;

namespace AnaparastasiGnosis
{
  public static class Program
  {
    public static void Main(string[] args)
    {
      string rdfFilePath = Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName + "/Erotima 3.rdf";

      Graph graph = new Graph();

      FileLoader.Load((IGraph) graph, rdfFilePath);

      LeviathanQueryProcessor sparqlQueryProcessor = new LeviathanQueryProcessor((ISparqlDataset) new InMemoryDataset((IGraph) graph));

      SparqlQueryParser sparqlQueryParser = new SparqlQueryParser();

      Console.WriteLine("Choose between A, B or C:");

      string str = Console.ReadLine();

      if (str == "A")
        Program.GetDepartmentInfo(sparqlQueryProcessor, sparqlQueryParser);
        
      if (str == "B")
        Program.AddNewTypeInstance(rdfFilePath);

      if (!(str == "C"))
        return;

      Program.SearchAllAssociatedTriples(graph);
    }

    public static List<SparqlResult> GetResultSet(
      this LeviathanQueryProcessor queryProcessor,
      SparqlQuery query)
    {
      return (queryProcessor.ProcessQuery(query) as SparqlResultSet).Results;
    }

    public static void GetDepartmentInfo(
      LeviathanQueryProcessor sparqlQueryProcessor,
      SparqlQueryParser sparqlQueryParser)
    {
      SparqlQuery fromString1 = sparqlQueryParser.ParseFromString("PREFIX uni:<http://www.mydomain.org/uni-ns/> SELECT ?departmentName WHERE { ?department a uni:Department. ?department uni:dep_name ?departmentName }");
      
      List<SparqlResult> resultSet1 = sparqlQueryProcessor.GetResultSet(fromString1);
      
      Console.WriteLine("Available Departments:\n");

      foreach (SparqlResult sparqlResult in resultSet1)
        Console.WriteLine("Number: " + (resultSet1.IndexOf(sparqlResult) + 1).ToString() + "    Department: " + ((object) sparqlResult[0])?.ToString());

      Console.WriteLine("\nPlease choose a department number:");

      LiteralNode literalNode = ((IEnumerable<KeyValuePair<string, INode>>) ((IEnumerable<SparqlResult>) resultSet1).ElementAt<SparqlResult>(int.Parse(Console.ReadLine()) - 1)).ElementAt<KeyValuePair<string, INode>>(0).Value as LiteralNode;
      
      SparqlQuery fromString2 = sparqlQueryParser.ParseFromString("PREFIX uni:<http://www.mydomain.org/uni-ns/> SELECT ?name ?phone ?email ?age WHERE { ?professor a uni:Professor. ?professor uni:has_name ?name. ?professor uni:has_phone ?phone. ?professor uni:has_email ?email. ?professor uni:has_age ?age. ?professor uni:member_of ?department. ?department uni:dep_name \"" + ((BaseLiteralNode) literalNode).Value + "\".}");
      
      List<SparqlResult> resultSet2 = sparqlQueryProcessor.GetResultSet(fromString2);

      Console.WriteLine("\nDepartment's Professor:\n\nName | Age | Phone Number | Email\n");

      foreach (SparqlResult sparqlResult in resultSet2)
        Console.WriteLine(((object) sparqlResult[2])?.ToString() + " | " + ((object) sparqlResult[0])?.ToString() + " | " + ((object) sparqlResult[3])?.ToString() + " | " + ((object) sparqlResult[1])?.ToString());
      
      SparqlQuery fromString3 = sparqlQueryParser.ParseFromString("PREFIX uni:<http://www.mydomain.org/uni-ns/> SELECT ?name ?phone ?email ?age WHERE { ?student a uni:Student. ?student uni:has_name ?name. ?student uni:has_phone ?phone. ?student uni:has_email ?email. ?student uni:has_age ?age. ?student uni:member_of ?department. ?department uni:dep_name \"" + ((BaseLiteralNode) literalNode).Value + "\".}");
      
      List<SparqlResult> resultSet3 = sparqlQueryProcessor.GetResultSet(fromString3);
      
      Console.WriteLine("\nDepartment's Students:\n\nName | Age | Phone Number | Email\n");

      foreach (SparqlResult sparqlResult in resultSet3)
        Console.WriteLine(((object) sparqlResult[2])?.ToString() + " | " + ((object) sparqlResult[0])?.ToString() + " | " + ((object) sparqlResult[3])?.ToString() + " | " + ((object) sparqlResult[1])?.ToString());
      
      SparqlQuery fromString4 = sparqlQueryParser.ParseFromString("PREFIX uni:<http://www.mydomain.org/uni-ns/> SELECT ?room_name ?room_capacity WHERE { ?classroom a uni:Classroom. ?classroom uni:room_name ?room_name. ?classroom uni:room_capacity ?room_capacity. ?classroom uni:room_department ?department. ?department uni:dep_name \"" + ((BaseLiteralNode) literalNode).Value + "\".}");
      
      List<SparqlResult> resultSet4 = sparqlQueryProcessor.GetResultSet(fromString4);
      
      Console.WriteLine("\nDepartment's Classroom:\n\nName | Capacity\n");

      foreach (SparqlResult sparqlResult in resultSet4)
        Console.WriteLine(((object) sparqlResult[1])?.ToString() + " | " + ((object) sparqlResult[0])?.ToString());
      
      SparqlQuery fromString5 = sparqlQueryParser.ParseFromString("PREFIX uni:<http://www.mydomain.org/uni-ns/> SELECT ?les_name WHERE { ?lesson uni:les_name ?les_name. ?lesson uni:taught_by ?professor. ?professor uni:member_of ?department. ?department uni:dep_name \"" + ((BaseLiteralNode) literalNode).Value + "\".}");
      
      List<SparqlResult> resultSet5 = sparqlQueryProcessor.GetResultSet(fromString5);
      
      Console.WriteLine("\nDepartment's Lessons:\n\nName\n");
      
      foreach (SparqlResult sparqlResult in resultSet5)
        Console.WriteLine((object) sparqlResult[0]);
    }

    public static void AddNewTypeInstance(string rdfFilePath)
    {
      Console.WriteLine("\nPlease choose a the number of the object type you want to add:");

      Console.WriteLine("\nNumber: 1  Object Type: Professor\nNumber: 2  Object Type: Student\nNumber: 3  Object Type: Department\nNumber: 4  Object Type: Lesson\nNumber: 5  Object Type: Classroom");

      int num = int.Parse(Console.ReadLine());

      string str1 = string.Empty;

      if (num <= 1 && num >= 6)
        return;

      if (num == 1)
      {
        Console.WriteLine("\nPlease add the object values:");

        Console.WriteLine("\nhas_name:");

        string str2 = Console.ReadLine();

        string str3 = str1 + "\n<rdf:Description rdf:about=\"http://www.mydomain.org/uni-ns/Professor/" + str2 + "\">" + "\n\t<uni:has_name>" + str2 + "</uni:has_name>";

        Console.WriteLine("\t\nhas_phone:");

        string str4 = str3 + "\n\t" + string.Format("<uni:has_phone>{0}</uni:has_phone>", (object) long.Parse(Console.ReadLine()));

        Console.WriteLine("\t\nhas_email:");

        string str5 = str4 + "\n\t<uni:has_email>" + Console.ReadLine() + "</uni:has_email>";

        Console.WriteLine("\nhas_age:");

        string str6 = str5 + "\n\t" + string.Format("<uni:has_age>{0}</uni:has_age>", (object) int.Parse(Console.ReadLine()));

        Console.WriteLine("\nmember_of:");

        string str7 = str6 + "\n\t<uni:member_of rdf:resource=\"http://www.mydomain.org/uni-ns/Department/" + Console.ReadLine() + "\"/>";

        Console.WriteLine("\nteaches:");

        str1 = str7 + "\n\t<uni:teaches rdf:resource=\"http://www.mydomain.org/uni-ns/Department/" + Console.ReadLine() + "\"/>" + "\n\t<uni:type rdf:resource=\"http://www.mydomain.org/uni-ns/Professor\"/>";
      }
      if (num == 2)
      {
        Console.WriteLine("\nPlease add the object values:");

        Console.WriteLine("\nhas_name:");

        string str8 = Console.ReadLine();

        string str9 = str1 + "\n<rdf:Description rdf:about=\"http://www.mydomain.org/uni-ns/Student/" + str8 + "\">" + "\n\t<uni:has_name>" + str8 + "</uni:has_name>";

        Console.WriteLine("\t\nhas_phone:");

        string str10 = str9 + "\n\t" + string.Format("<uni:has_phone>{0}</uni:has_phone>", (object) long.Parse(Console.ReadLine()));

        Console.WriteLine("\t\nhas_email:");

        string str11 = str10 + "\n\t<uni:has_email>" + Console.ReadLine() + "</uni:has_email>";

        Console.WriteLine("\nhas_age:");

        string str12 = str11 + "\n\t" + string.Format("<uni:has_age>{0}</uni:has_age>", (object) int.Parse(Console.ReadLine()));

        Console.WriteLine("\nmember_of:");

        str1 = str12 + "\n\t<uni:member_of rdf:resource=\"http://www.mydomain.org/uni-ns/Department/" + Console.ReadLine() + "\"/>" + "\n\t<uni:type rdf:resource=\"http://www.mydomain.org/uni-ns/Student\"/>";
      }
      if (num == 3)
      {
        Console.WriteLine("\nPlease add the object values:");

        Console.WriteLine("\ndep_name:");

        string str13 = Console.ReadLine();

        string str14 = str1 + "\n<rdf:Description rdf:about=\"http://www.mydomain.org/uni-ns/Department/" + str13 + "\">" + "\n\t<uni:dep_name>" + str13 + "</uni:dep_name>";

        Console.WriteLine("\t\ndep_city:");

        str1 = str14 + "\n\t<uni:dep_city>" + Console.ReadLine() + "</uni:dep_city>" + "\n\t<uni:type rdf:resource=\"http://www.mydomain.org/uni-ns/Department\"/>";
      }
      if (num == 4)
      {
        Console.WriteLine("\nPlease add the object values:");

        Console.WriteLine("\nles_name:");

        string str15 = Console.ReadLine();

        string str16 = str1 + "\n<rdf:Description rdf:about=\"http://www.mydomain.org/uni-ns/Lesson/" + str15 + "\">" + "\n\t<uni:les_name>" + str15 + "</uni:les_name>";

        Console.WriteLine("\t\ntaught_by:");

        str1 = str16 + "\n\t<uni:taught_by rdf:resource=\"http://www.mydomain.org/uni-ns/Lesson/" + Console.ReadLine() + "\"/>";
      }
      if (num == 5)
      {
        Console.WriteLine("\nPlease add the object values:");

        Console.WriteLine("\nroom_name:");

        string str17 = Console.ReadLine();

        string str18 = str1 + "\n<rdf:Description rdf:about=\"http://www.mydomain.org/uni-ns/Classroom/" + str17 + "\">" + "\n\t<uni:room_name>" + str17 + "</uni:room_name>";

        Console.WriteLine("\t\nroom_capacity:");

        string str19 = str18 + "\n\t" + string.Format("<uni:room_capacity>{0}</uni:room_capacity>", (object) int.Parse(Console.ReadLine()));

        Console.WriteLine("\t\nroom_department:");

        str1 = str19 + "\n\t<uni:room_department rdf:resource=\"http://www.mydomain.org/uni-ns/Department/" + Console.ReadLine() + "\"/>" + "\n\t<uni:type rdf:resource=\"http://www.mydomain.org/uni-ns/Classroom\"/>";
      }
      string str20 = str1 + "\n</rdf:Description>" + "\n</rdf:RDF>";

      Program.DeleteLastLine(rdfFilePath);

      using (StreamWriter streamWriter = File.AppendText(rdfFilePath))
        streamWriter.WriteLine(str20);

      Console.WriteLine("New object was successfully written.");
    }

    public static void SearchAllAssociatedTriples(Graph graph)
    {
      Console.WriteLine("\nPlease enter the resource Uri:");

      string uriString = Console.ReadLine();

      StaticRdfsReasoner staticRdfsReasoner = new StaticRdfsReasoner();

      staticRdfsReasoner.Initialise((IGraph) graph);

      staticRdfsReasoner.Apply((IGraph) graph);

      IUriNode uriNode = ((BaseGraph) graph).CreateUriNode(new Uri(uriString));

      IEnumerable<Triple> triples = ((BaseGraph) graph).GetTriples((INode) uriNode);

      Console.WriteLine("\nFetched Resources:\n");

      foreach (object obj in triples)
        Console.WriteLine(obj);
    }

    public static void DeleteLastLine(string filepath)
    {
      List<string> list = ((IEnumerable<string>) File.ReadAllLines(filepath)).ToList<string>();

      File.WriteAllLines(filepath, list.GetRange(0, list.Count - 1).ToArray());
    }
  }
}
