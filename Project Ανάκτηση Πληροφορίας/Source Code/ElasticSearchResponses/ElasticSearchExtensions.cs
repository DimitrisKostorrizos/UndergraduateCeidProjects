using Nest;

using System.Collections.Generic;

namespace Anaktisi
{
    /// <summary>
    /// The elastic client extension methods
    /// </summary>
    public static class ElasticSearchExtensions
    {
        /// <summary>
        /// Bulk index the <paramref name="documents"/> in the selected index <paramref name="index"/>
        /// </summary>
        /// <typeparam name="TClass">The type of the documents</typeparam>
        /// <param name="client">The elastic search client</param>
        /// <param name="documents">The documents</param>
        /// <param name="index">The index name</param>
        /// <returns>The response</returns>
        public static IResponse BulkIndexDocuments<TClass>(this ElasticClient client, IEnumerable<TClass> documents, IndexName index)
            where TClass : class
        {
            // Check if the index exists
            var indexExistsResponse = client.Indices.Exists(index);

            // If the index exists...
            if (indexExistsResponse.Exists)
            {
                // Delete the index
                var indexDeletionResponse = client.Indices.Delete(index);

                // If the response is not valid...
                if (!indexDeletionResponse.IsValid)
                    return indexDeletionResponse;
            }

            // Create the index
            var indexCreationResponse = client.Indices.Create(index, x => x.Map<TClass>(y => y.AutoMap()));

            // If the response is not valid...
            if (!indexCreationResponse.IsValid)
                return indexCreationResponse;

            // Bulk index the documents
            var asyncIndexResponse = client.Bulk(x => x.Index(index).IndexMany(documents));

            // Return the response
            return asyncIndexResponse;
        }
    }
}
