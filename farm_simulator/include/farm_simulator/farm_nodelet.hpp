/**
 * @file
 *
 * \brief  Declaration of nodelet for managing the farm simulation
 * \author Corentin Chauvin-Hamea
 * \date   2019
 */

#ifndef FARM_NODELET_HPP
#define FARM_NODELET_HPP

#include "farm_common.hpp"
#include "farm_simulator/FarmSimulatorConfig.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <string>
#include <vector>
#include <csignal>


namespace mfcpp {
  /**
   * \brief  Nodelet class for farm simulation
   */
  class FarmNodelet: public nodelet::Nodelet {
    public:
      FarmNodelet();
      ~FarmNodelet();

      /**
       * \brief  Function called at beginning of nodelet execution
       */
      virtual void onInit();

    private:
      // Static members
      static sig_atomic_t volatile b_sigint_;  ///<  Whether SIGINT signal has been received

      // Private members
      ros::NodeHandle nh_;            ///<  Node handler (for topics and services)
      ros::NodeHandle private_nh_;    ///<  Private node handler (for parameters
      ros::Publisher rviz_pub_;       ///<  ROS publisher for Rviz
      std::vector<AlgaeLine> algae_lines_;  ///<  Vector of all the algae in the farm
      bool reconfigure_initialised_;  ///<  Whether the dynamic reconfigure callback
                                      ///<  has been called once

      // ROS parameters
      float main_loop_freq_;  ///<  Frequency of the main loop

      int nbr_lines_;       ///<  Number of algae lines
      float offset_lines_;  ///<  Lateral distance (m) between each line
      float length_lines_;  ///<  Length (m) of each line
      float thickness_lines_;  ///<  Diameter (m) of each line
      float depth_lines_;   ///<  Distance (m) between water surface and line
      float depth_water_;   ///<  Distance (m) between water surface and seafloor
      float anchors_diameter_;  ///<  Diameter (m) of the cylindrical anchors
      float anchors_height_;    ///<  Height (m) of the cylindrical anchors

      bool randomise_lines_;    ///<  Whether to randomise the position of each line
      float mean_phi_lines_;    ///<  Mean of phi angle for algae line generation
      float mean_theta_lines_;  ///<  Mean of theta angle for algae line generation
      float bnd_phi_lines_;     ///<  Bound such that phi is sampled in [mean-bnd, mean+bnd]
      float bnd_theta_lines_;   ///<  Bound such that theta is sampled in [mean-bnd, mean+bnd]
      float bnd_gamma_lines_;   ///<  Bound such that gamma is sampled in [mean-bnd, mean+bnd]

      /**
       * \brief  Main loop of the nodelet
       */
      void run_nodelet();

      /**
       * \brief  SINGINT (Ctrl+C) callback to stop the nodelet properly
       */
      static void sigint_handler(int s);

      /**
       * \brief  Callback for dynamic reconfigure
       *
       * \param  New configuration
       * \param  Change level
       */
      void reconfigure_callback(farm_simulator::FarmSimulatorConfig &config,
        uint32_t level);

      /**
       * \brief  Initialise the algae lines
       */
      void init_algae_lines();

      /**
       * \brief  Displays objects by publishing Rviz markers
       *
       * \param duration  Duration of the marker (in sec)
       */
      void pub_rviz_markers(float duration) const;

  };



}  // namespace mfcpp

#endif