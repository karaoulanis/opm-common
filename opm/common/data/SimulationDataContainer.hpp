/*
  Copyright 2016 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPM_COMMON_DATA_SIMULATIONDATACONTAINER_H_
#define OPM_COMMON_DATA_SIMULATIONDATACONTAINER_H_

#include <cstddef>
#include <string>
#include <map>
#include <utility>
#include <vector>

namespace Opm {
/**
 * @class SimulationDataContainer
 * @brief A simple container to manage simulation data.
 * 
 * The container is instantiated with information of how many cells,
 * faces and phases are present in the reservoirmodel. 
 * You can then add data to the container by using the
 * 
 * - registerCellData()
 * - registerFaceData()
 * 
 * functions. The container owns and manages the data, but
 * mutable references are returned with the getCellData() and
 * getFaceData() methods, and the content will typically be
 * modified by external scope.
 */
class SimulationDataContainer {
 public:
  /**
   * @brief Main constructor setting the sizes for the contained data types.
   * @param num_cells number of elements in cell data vectors
   * @param num_faces   number of elements in face data vectors
   * @param num_phases  number of phases, the number of components
   *                    in any data vector must equal 1 or this
   *                    number
   * @deprecated @p num_phases behaviour and argument
   */
  SimulationDataContainer(size_t num_cells, size_t num_faces,
                          size_t num_phases);

  /**
   * @brief Copy constructor.
   * 
   * Must be defined explicitly because class contains non-value objects (the 
   * reference pointers pressure_ref_ etc.) that should not simply be copied.
   */
  SimulationDataContainer(const SimulationDataContainer&);

  /**
   * @brief Copy assignment operator.
   * 
   * Must be defined explicitly because class contains non-value objects (the 
   * reference pointers pressure_ref_ etc.) that should not simply be copied.
   */
  SimulationDataContainer& operator=(const SimulationDataContainer&);

  /**
   * @brief  Efficient O(1) swap.
   */
  void swap(SimulationDataContainer&);

  /**
   * @brief Get the number of phases.
   * @todo Inline this getter, it looks relatively cheap.
   */
  size_t numPhases() const;

  /**
   * @brief Get the number of faces.
   * @todo Inline this getter, it looks relatively cheap.
   */
  size_t numFaces() const;

  /**
   * @brief Get the number of cells.
   * @todo Inline this getter, it looks relatively cheap.
   */
  size_t numCells() const;

  /**
   * @brief Check whether a cell is in the container.
   * @param name the name of the cell
   * @return true if found
   */
  bool hasCellData(const std::string& name) const;

  /**
   * @brief Register a cell data vector of size numCells() * components.
   * @param name the name of the data vector
   * @param components the number of components related to each cell
   * @param initialValue initialization value for the vector
   */
  void registerCellData(const std::string& name, size_t components,
                        double initialValue = 0.0);

  /**
   * @brief Retrieve a stored cell data vector 
   * @param name the name of the vector
   * @return a reference to a vector of size numCells() * components
   */
  std::vector<double>& getCellData(const std::string& name);

  /**
   * @brief Retrieve a stored cell data vector 
   * @param name the name of the vector
   * @return a const reference to a vector of size numCells() * components
   */
  const std::vector<double>& getCellData(const std::string& name) const;

  /**
   * @brief Check whether a face is in the container.
   * @param name the name of the face
   * @return true if found
   */
  bool hasFaceData(const std::string& name) const;

  /**
   * @brief Register a face data vector of size numCells() * components.
   * @param name the name of the data vector
   * @param components the number of components related to each face
   * @param initialValue initialization value for the vector
   */
  void registerFaceData(const std::string& name, size_t components,
                        double initialValue = 0.0);

  /**
   * @brief Retrieve a stored face data vector 
   * @param name the name of the vector
   * @return a reference to a vector of size numCells() * components
   */
  std::vector<double>& getFaceData(const std::string& name);

  /**
   * @brief Retrieve a stored face data vector 
   * @param name the name of the vector
   * @return a const reference to a vector of size numCells() * components
   */
  const std::vector<double>& getFaceData(const std::string& name) const;

  /**
   * @brief Return the number of components of the cell data vector.
   * 
   * The number of components are defined as:
   * - <tt>numCellDataComponents("PRESSURE")   -> 1</tt>
   * - <tt>numCellDataComponents("SATURATION") -> 3</tt>
   * 
   * for a three phase model.
   * @param name The name of the cell data vector
   */
  size_t numCellDataComponents(const std::string& name) const;

  /**
   * @brief Check for equality between two containers
   * @param other the other container to be tested
   * @return true if equal
   */
  bool equal(const SimulationDataContainer& other) const;

  /**
   * @brief Set values in a cell data vector
   * @param key the name of the cell data vector
   * @param component the component to be modified
   * @param cells cell indices to be modified
   * @param values new values to be assigned
   */
  void setCellDataComponent(const std::string& key, size_t component,
                            const std::vector<int>& cells,
                            const std::vector<double>& values);

  /**
   * @brief Get pressure (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline std::vector<double>& pressure() {
    return *pressure_ref_;
  }

  /**
   * @brief Get temperature (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline std::vector<double>& temperature() {
    return *temperature_ref_;
  }

  /**
   * @brief Get saturation (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline std::vector<double>& saturation() {
    return *saturation_ref_;
  }

  /**
   * @brief Get facepressure (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline std::vector<double>& facepressure() {
    return *facepressure_ref_;
  }

  /**
   * @brief Get faceflux (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline std::vector<double>& faceflux() {
    return *faceflux_ref_;
  }

  /**
   * @brief Get pressure (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline const std::vector<double>& pressure() const {
      return *pressure_ref_;
  }

  /**
   * @brief Get temperature (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline const std::vector<double>& temperature() const {
    return *temperature_ref_;
  }

  /**
   * @brief Get saturation (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline const std::vector<double>& saturation() const {
    return *saturation_ref_;
  }

  /**
   * @brief Get facepressure (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline const std::vector<double>& facepressure() const {
    return *facepressure_ref_;
  }

  /**
   * @brief Get faceflux (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  inline const std::vector<double>& faceflux() const {
    return *faceflux_ref_;
  }

  /**
   * @brief Get cell data set (immutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  const std::map<std::string, std::vector<double>>& cellData() const;

  /**
   * @brief Get cell data set (mutable)
   * @deprecated will eventually be moved to concrete subclasses
   */
  std::map<std::string, std::vector<double>>& cellData();

 private:
  /**
   * @brief Adds default fields 
   * @deprecated It should not be used any more.
   */
  void addDefaultFields();

  /**
   * @brief Sets the reference pointers for the fast accessors,
   *        
   * The fields must be created first by copying or a call to
   * addDefaultFields().
   */
  void setReferencePointers();

  size_t m_num_cells;  //!< number of cells
  size_t m_num_faces;  //!< number of faces
  size_t m_num_phases;  //!< number of phases
  std::map< std::string, std::vector<double> > m_cell_data;  //!< cell data set
  std::map< std::string, std::vector<double> > m_face_data;  //!< face data set
  std::vector<double>* pressure_ref_;  //!< the pressure
  std::vector<double>* temperature_ref_;  //!< the temperature
  std::vector<double>* saturation_ref_;  //!< the saturation
  std::vector<double>* facepressure_ref_;  //!< the face pressure
  std::vector<double>* faceflux_ref_;  //!< the face flux
};
}  // namespace Opm
#endif  // OPM_COMMON_DATA_SIMULATIONDATACONTAINER_H_
