#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html.h"


namespace snu {

    void makeDSHtml(const char *name, StatResult& result, Plot& plot)
    {
		std::string real_name = name + std::string(".html");
        FILE *fp = fopen(real_name.c_str(), "w");

        fprintf(fp, "\
        <!DOCTYPE html>\
        <html>\
            <head>\
                <meta charset = \"utf-8\">\
                <title>SNU Graph Analysis Tool</title>\
                <style type=\"text/css\">\
                    h1{\
                        text-indent: 1em;\
                    }\
                    h2{\
                        text-indent: 2em;\
                    }\
                    h3{\
                        text-indent: 4em;\
                    }\
                </style>\
            </head>\
            <body>\
                <h1><p>SNU Graph Analysis Tool</p></h1>");

        fprintf(fp, "\
            <h2>\
                Graph Information\
            </h2>\
            <h3>\
                <p> graph name: %s </p>\
                <p> graph type: directed simple graph </p>\
            </h3>\
        ", name);

        //if (result) {
            if (result.basicstat)
                fprintf(fp, "\
                    <h2>\
                        Basic Statistics\
                    </h2>\
                    <h3>\
                        <p> size = %lld </p>\
                        <p> volume = %lld </p>\
                        <p> number of vertex labels = %lld </p>\
                        <p> number of edge labels = %lld </p>\
                        <p> density = %lf </p>\
                        <p> maximum indegree = %lld </p>\
                        <p> maximum outdegree = %lld </p>\
                        <p> maximum size of vertex label = %lld </p>\
                        <p> maximum size of edge label = %lld </p>\
                        <p> reciprocity = %lf </p>\
                        <p> negativity = %lf </p>\
                    </h3>\
                ", result.size, result.volume, result.num_vlabel, result.num_elabel
                , result.density, result.max_indegree, result.max_outdegree
                , result.max_vlabel_size, result.max_elabel_size, result.reciprocity
                , result.negativity);


            if (result.connectstat)
                fprintf(fp, "\
                    <h2>\
                        Connectivity Statistics\
                    </h2>\
                    <h3>\
                        <p> number of strongly connected components = %lld </p>\
                        <p> size of largest strongly connected component = %lld </p>\
                        <p> number of weakly connected components = %lld </p>\
                        <p> size of largest weakly connected component = %lld </p>\
                    </h3>\
                ", result.num_scc, result.size_lscc, result.num_wcc, result.size_lwcc);

            if (result.eigencentralitystat) {
                fprintf(fp, "\
                    <h2>\
                        Eigenvector Centrality Statistics\
                    </h2>\
                    <h3>\
                    <p> max eigenvalue = %lf</p>", result.max_eigenvalue);
                if (result.eigencentrality_converged) {
                    fprintf(fp, "<p> max eigenvector centrality value = %lf at ID = %lld </p>",
                            result.max_eigencentrality, result.max_eigencentrality_id);
                } else {
                    fprintf(fp, "<p> eigenvector centrality failed to converge. </p>");
                }
                if (result.pagerank_converged) {
                    fprintf(fp, "<p> max PageRank value = %lf at ID = %lld </p>",
                            result.max_pagerank, result.max_pagerank_id);
                } else {
                    fprintf(fp, "<p> PageRank failed to converge. </p>");
                }
                if (result.katz_centrality_computed) {
                    fprintf(fp, "<p> max katz centrality value = %lf at ID = %lld </p>",
                            result.max_katz_centrality, result.max_katz_centrality_id);
                }
                fprintf(fp, "</h3>");
            }

            if (result.biconnectedstat)
                fprintf(fp, "\
                    <h2>\
                        Biconnected Component Statistics\
                    </h2>\
                    <h3>\
                        <p> number of articulation points (ARP) = %lld </p>\
                        <p> number of biconnected components (BCC) = %lld </p>\
                        <p> size of largest biconnected component = %lld </p>\
                        <p> maximum number of BCC's connected to a single ARP = %lld </p>\
                    </h3>\
                ", result.num_arp, result.num_bcc, result.size_lbcc, result.max_conn_bcc);
        //}

        if (plot.makeplot)
            fprintf(fp, "\
                <h2>\
                    Statistics Image\
                </h2>\
                <h3>\
                    <p> label-vertex image </p>\
                    <img src=\"pyplot/%s_label-vertex.png\" width=\"400\" alt=\"label-vertex image\">\
                    <img src=\"pyplot/%s_label-vertex_log.png\" width=\"400\" alt=\"log scale label-vertex image\">\
                </h3>\
                <h3>\
                    <p> indegree image </p>\
                    <img src=\"pyplot/%s_indegree.png\" width=\"400\" alt=\"indegree image\">\
                    <img src=\"pyplot/%s_indegree_log.png\" width=\"400\" alt=\"log scale indegree image\">\
                </h3>\
                <h3>\
                    <p> outdegree image </p>\
                    <img src=\"pyplot/%s_outdegree.png\" width=\"400\" alt=\"outdegree image\">\
                    <img src=\"pyplot/%s_outdegree_log.png\" width=\"400\" alt=\"log scale outdegree image\">\
                </h3>\
            ", plot.name.c_str(), plot.name.c_str(), plot.name.c_str(), plot.name.c_str(), plot.name.c_str(), plot.name.c_str());
        
        fprintf(fp, "</body></html>");
        fclose(fp);
    }

    void makeUSHtml(const char *name, StatResult& result, Plot& plot)
    {
		std::string real_name = name + std::string(".html");
        FILE *fp = fopen(real_name.c_str(), "w");
        
        fprintf(fp, "\
        <!DOCTYPE html>\
        <html>\
            <head>\
                <meta charset = \"utf-8\">\
                <title>SNU Graph Analysis Tool</title>\
                <style type=\"text/css\">\
                    h1{\
                        text-indent: 1em;\
                    }\
                    h2{\
                        text-indent: 2em;\
                    }\
                    h3{\
                        text-indent: 4em;\
                    }\
                </style>\
            </head>\
            <body>\
                <h1><p>SNU Graph Analysis Tool</p></h1>");
        
        fprintf(fp, "\
            <h2>\
                Graph Information\
            </h2>\
            <h3>\
                <p> graph name: %s </p>\
                <p> graph type: undirected simple graph </p>\
            </h3>\
        ", name);

        //if (result) {
            if(result.basicstat)
                fprintf(fp, "\
                    <h2>\
                        Basic Statistics\
                    </h2>\
                    <h3>\
                        <p> size = %lld </p>\
                        <p> volume = %lld </p>\
                        <p> number of vertex labels = %lld </p>\
                        <p> number of edge labels = %lld </p>\
                        <p> density = %lf </p>\
                        <p> average degree = %lf </p>\
                        <p> maximum degree = %lld </p>\
                        <p> maximum size of vertex label = %lld </p>\
                        <p> maximum size of edge label = %lld </p>\
                        <p> negativity = %lf </p>\
                    </h3>\
                ", result.size, result.volume, result.num_vlabel, result.num_elabel
                , result.density, result.avg_degree, result.max_degree
                , result.max_vlabel_size, result.max_elabel_size, result.negativity);

            if (result.connectstat)
                fprintf(fp, "\
                    <h2>\
                        Connectivity Statistics\
                    </h2>\
                    <h3>\
                        <p> number of connected components = %lld </p>\
                        <p> size of largest connected component = %lld </p>\
                        <p> approximate diameter (largest distance of all shortest path) = %lld </p>\
                    </h3>\
                ", result.num_cc, result.size_lcc, result.diameter);

            if (result.eigencentralitystat) {
                fprintf(fp, "\
                        <h2>\
                            Eigenvector Centrality Statistics\
                        </h2>\
                        <h3>\
                        <p> max eigenvalue = %lf</p>", result.max_eigenvalue);
                if (result.eigencentrality_converged) {
                    fprintf(fp, "<p> max eigenvector centrality value = %lf at ID = %lld </p>",
                            result.max_eigencentrality, result.max_eigencentrality_id);
                } else {
                    fprintf(fp, "<p> eigenvector centrality failed to converge. </p>");
                }
                if (result.pagerank_converged) {
                    fprintf(fp, "<p> max PageRank value = %lf at ID = %lld </p>",
                            result.max_pagerank, result.max_pagerank_id);
                } else {
                    fprintf(fp, "<p> PageRank failed to converge. </p>");
                }
                if (result.katz_centrality_computed) {
                    fprintf(fp, "<p> max Katz centrality value = %lf at ID = %lld </p>",
                            result.max_katz_centrality, result.max_katz_centrality_id);
                }
                fprintf(fp, "</h3>");
            }
            if (result.biconnectedstat) {
                fprintf(fp, "\
                    <h2>\
                        Biconnected Component Statistics\
                    </h2>\
                    <h3>\
                        <p> number of articulation points (ARP) = %lld </p>\
                        <p> number of biconnected components (BCC) = %lld </p>\
                        <p> size of largest biconnected component = %lld </p>\
                        <p> maximum number of BCC's connected to a single ARP = %lld </p>\
                    </h3>\
                ", result.num_arp, result.num_bcc, result.size_lbcc, result.max_conn_bcc);
            }
            if (result.closenessstat) {
                fprintf(fp, "\
                    <h2>\
                        Closeness Centrality Statistics\
                    </h2>\
                    <h3>\
                        <p> max closeness centrality value = %lf at ID = %lld </p>\
                    </h3>",
                            result.max_closeness_centrality, result.max_closeness_centrality_id);
            }
            if (result.betweennessstat) {
                fprintf(fp, "\
                    <h2>\
                        Betweenness Centrality Statistics\
                    </h2>\
                    <h3>\
                        <p> max betweenness centrality value = %lf at ID = %lld </p>\
                    </h3>",
                            result.max_betweenness_centrality, result.max_betweenness_centrality_id);
            }
            if (result.countstat)
                fprintf(fp, "\
                    <h2>\
                        Count statistics\
                    </h2>\
                    <h3>\
                        <p> number of wedges = %llu </p>\
                        <p> number of claws = %llu </p>\
                        <p> number of triangles = %llu </p>\
                    </h3>\
                ", result.wedge_count, result.claw_count, result.triangle_count);
        //}

        if (plot.makeplot)
            fprintf(fp, "\
                <h2>\
                    Statistics Image\
                </h2>\
                <h3>\
                    <p> label-vertex image </p>\
                    <img src=\"pyplot/%s_label-vertex.png\" width=\"400\" alt=\"label-vertex image\">\
                    <img src=\"pyplot/%s_label-vertex_log.png\" width=\"400\" alt=\"log scale label-vertex image\">\
                </h3>\
                <h3>\
                    <p> degree image </p>\
                    <img src=\"pyplot/%s_degree.png\" width=\"400\" alt=\"degree image\">\
                    <img src=\"pyplot/%s_degree_log.png\" width=\"400\" alt=\"log scale degree image\">\
                </h3>\
            ", plot.name.c_str(), plot.name.c_str(), plot.name.c_str(), plot.name.c_str());
        
        fprintf(fp, "</body></html>");
        fclose(fp);
    }
}

