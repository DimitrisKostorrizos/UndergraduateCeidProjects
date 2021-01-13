using System;
using System.IO;
using System.Linq;

using VDS.RDF;
using VDS.RDF.Ontology;
using VDS.RDF.Parsing;
using VDS.RDF.Query.Inference;

namespace AnaparastasiGnosis
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            // Initialize the file path to owl file
            var owlFilePath = Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName + "/DnD_Classes_Ontology.owl";

            // Declare a owl graph
            var owlGraph = new OntologyGraph();

            // Load the owl file
            FileLoader.Load(owlGraph, owlFilePath);

            // Declare a owl inference reasoner
            var infernceReasoner = new StaticRdfsReasoner();

            // Initialize using the owl file
            infernceReasoner.Initialise(owlGraph);

            // Apply the owl to the inference reasoner
            infernceReasoner.Apply(owlGraph);

            Console.WriteLine("\nOptions:\n1 to search for the instances based on a property\n2 to add new instances\n3 to search for instances based on a class");

            // Read the user choice
            var input = int.Parse(Console.ReadLine());

            if (input == 1)
                // Search for instances in the owl file
                SearchInstances(owlGraph);

            if (input == 2)
                // Add new instances in the owl file
                AddInstances(owlGraph, owlFilePath);

            if (input == 3)
                // Print the  instances in the owl file
                PrintInstances(owlGraph);
        }


        /// <summary>
        /// The function for printing the instances
        /// </summary>
        /// <param name="ontologyGraph">The owl graph</param>
        public static void SearchInstances(OntologyGraph ontologyGraph)
        {
            // Get all defined properties
            var properties = ontologyGraph.AllProperties;

            // For every property...
            foreach (var property in properties)
            {
                // Print the property name
                Console.WriteLine(property.Resource);
            }

            Console.WriteLine("\nEnter the Uri of the property.\n");

            // Read the user choice
            var selectedUri = new Uri(Console.ReadLine());

            // Get the selected property
            var selectedProperty = properties.First(x => x.Resource.ToString() == selectedUri.ToString());

            Console.WriteLine("\nEnter the property value:\n");

            // Read the user choice
            var input = Console.ReadLine();

            // Get all the triples
            var triples = selectedProperty.TriplesWithPredicate.Where(x =>
            {
                // If the object node is literal...
                if (x.Object.NodeType == NodeType.Literal)
                {
                    // Typecast the node
                    var node = x.Object as LiteralNode;

                    // Check the value
                    return node.Value == input;
                }
                else
                {
                    // Typecast the node
                    var node = x.Object as UriNode;

                    // Check the uri
                    return node.Uri.ToString() == input;
                }
            });

            Console.WriteLine("\nInstances:\n");

            // For every triple...
            foreach (var triple in triples)
            {
                // Print the triple subject
                Console.WriteLine(triple.Subject);
            }
        }

        /// <summary>
        /// The function for adding instances
        /// </summary>
        /// <param name="ontologyGraph">The owl graph</param>
        /// <param name="owlFilePath">The owl file path</param>
        public static void AddInstances(OntologyGraph ontologyGraph, string owlFilePath)
        {
            // Declare an empty uri node
            var uriNode = ontologyGraph.CreateUriNode();

            // Set the uri of the node
            uriNode.GraphUri = new Uri(Console.ReadLine());

            // Add the uri node as an individual
            ontologyGraph.CreateIndividual(uriNode);

            // Save the graph to the file
            ontologyGraph.SaveToFile(owlFilePath);

            Console.WriteLine("Updated was successful.");
        }

        /// <summary>
        /// The function for printing instances
        /// </summary>
        /// <param name="ontologyGraph">The owl graph</param>
        public static void PrintInstances(OntologyGraph ontologyGraph)
        {
            // Get all classes
            var classes = ontologyGraph.AllClasses;

            // For every class...
            foreach (var owlClass in classes)
            {
                // Print the uri
                Console.WriteLine(owlClass.Resource);
            }

            Console.WriteLine("Enter the Uri of the class.\n");

            // Read the user choice
            var selectedUri = new Uri(Console.ReadLine());

            Console.WriteLine("\nClass Instances:\n");

            // Get the selected class
            var selectedClass = classes.First(x => x.Resource.ToString() == selectedUri.ToString());

            // For every class...
            foreach (var instance in selectedClass.Instances)
            {
                // Print the uri
                Console.WriteLine(instance.Resource);
            }
        }
    }
}
