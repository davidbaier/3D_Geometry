#include "Smoothing.hh"


// ======================================================================
// EXERCISE 1.1
// ========================================================================
void Smoothing::uniform_smooth(const int _iterations) {
    Point laplacian;
    int w = 0.;
    std::vector<Point> points_new(mesh_.n_vertices(), Point(0.));
    for (auto vh : mesh_.vertices())
        points_new[vh.idx()] = mesh_.point(vh);

    for (int iter=0; iter<_iterations; ++iter) {
        // ------------- IMPLEMENT HERE ---------
        int weight = 1;
        for(auto vh : mesh_.vertices()){
            if(!mesh_.is_boundary(vh)){
                auto sum_weights = 0;
                auto time_step_diffusion = 0.3;
                //Iterate over one-ring neighborhood
                for(auto vv_itr = mesh_.vv_iter(vh); vv_itr.is_valid(); ++vv_itr){
                    laplacian += weight*(mesh_.point(*vv_itr)-mesh_.point(vh));
                    sum_weights++;
                }
                laplacian /=sum_weights;
                points_new[vh.idx()] = mesh_.point(vh) + (time_step_diffusion*laplacian);
            }
        }
        // ------------- IMPLEMENT HERE ---------
        // update vertex positions
        for (auto vh : mesh_.vertices()) {
            mesh_.point(vh) = points_new[vh.idx()];
        }
    }

    mesh_.update_normals();
}

// ======================================================================
// EXERCISE 1.2
// ========================================================================
void Smoothing::cotan_laplacian_smooth(const int _iterations) {
    Point laplacian;
    double ww = 0.;
    std::vector<Point> points_new(mesh_.n_vertices(), Point(0.));
    for (auto vh : mesh_.vertices())
        points_new[vh.idx()] = mesh_.point(vh);

    for (int iter=0; iter<_iterations; ++iter) {
        // update edge weights
        calc_edges_weights();
        // ------------- IMPLEMENT HERE ---------
        auto weight = 0.0;
        for(auto vh : mesh_.vertices()){
            if(!mesh_.is_boundary(vh)){
                auto sum_weights = 0.0;
                auto time_step_diffusion = 0.3;
                //Iterate over edges from current vertex
                for(auto ve_itr = mesh_.vih_iter(vh); ve_itr.is_valid(); ++ve_itr){
                    auto edge_handle = mesh_.edge_handle(*ve_itr);
                    weight = mesh_.property(edge_weight_, edge_handle);
                    
                    laplacian += weight*(mesh_.point(mesh_.from_vertex_handle(*ve_itr))-mesh_.point(vh));
                    sum_weights+=weight;
                }
                laplacian /=sum_weights;
                points_new[vh.idx()] = mesh_.point(vh) + (time_step_diffusion*laplacian);
            }
        }
        // ------------- IMPLEMENT HERE ---------
        // update vertex positions
        for (auto vh : mesh_.vertices()) {
            mesh_.point(vh) = points_new[vh.idx()];
        }
    }

    mesh_.update_normals();
}

// ======================================================================
// EXERCISE 2
// ========================================================================
void Smoothing::implicit_smooth(const double _timestep) {
    int n = (int)mesh_.n_vertices();
    // compute cotan edge weights and vertex areas
    calc_weights();
    // ------------- IMPLEMENT HERE ---------

    // ------------- IMPLEMENT HERE ---------
    mesh_.update_normals();
}

// ======================================================================
// EXERCISE 3.1
// ========================================================================
void Smoothing::uniform_laplacian_enhance_feature(const int _iterations, const int _coefficient) {
    // ------------- IMPLEMENT HERE ---------
    auto mesh_old_ = mesh_;
    uniform_smooth(_iterations);

    for(auto vh : mesh_.vertices()){
        if(!mesh_.is_boundary(vh)){
            mesh_.point(vh) = mesh_.point(vh)+_coefficient*(mesh_old_.point(vh)-mesh_.point(vh));
        }
    }

    // ------------- IMPLEMENT HERE ---------
    mesh_.update_normals();
}

// ======================================================================
// EXERCISE 3.2
// ========================================================================
void Smoothing::cotan_laplacian_enhance_feature(const int _iterations, const int _coefficient) {
    // ------------- IMPLEMENT HERE ---------
    auto mesh_old_ = mesh_;
    cotan_laplacian_smooth(_iterations);

    for(auto vh : mesh_.vertices()){
        if(!mesh_.is_boundary(vh)){
            mesh_.point(vh) = mesh_.point(vh)+_coefficient*(mesh_old_.point(vh)-mesh_.point(vh));
        }
    }
    // ------------- IMPLEMENT HERE ---------
    mesh_.update_normals();
}