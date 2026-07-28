
#include <Python.h>
#include <qiskit.h>
#include <stdint.h>

static PyObject *build_special_circuit(PyObject *self, PyObject *args) {
    QkCircuit *qc = qk_circuit_new(6, 0);

    // TODO 1: Apply H to qubit 0.
    //   Use qk_circuit_gate with QkGate_H. See the C API reference.
    qk_circuit_gate(qc, QkGate_H, (uint32_t[]){0}, NULL);

    // TODO 2: Apply X to qubit 1.
    //   Use qk_circuit_gate with QkGate_X.
    qk_circuit_gate(qc, QkGate_X, (uint32_t[]){1}, NULL);

    // TODO 3: Add a CNOT chain. Control is qubit 0, targets are 1 to 5.
    //   For each target, call qk_circuit_gate with QkGate_CX and a {control, target} array.
    //   A for loop works here.
    for (uint32_t target = 1; target <= 5; target++) {
        uint32_t qubits[2] = {0, target};
        qk_circuit_gate(qc, QkGate_CX, qubits, NULL);
    }
    return qk_circuit_to_python_full(qc);
}

static PyMethodDef methods[] = {
    {"build_special_circuit", build_special_circuit, METH_NOARGS, "Build the special circuit."},
    {NULL, NULL, 0, NULL},
};
static struct PyModuleDef moduledef = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "qgss_circuit",
    .m_methods = methods,
};
PyMODINIT_FUNC PyInit_qgss_circuit(void) {
    if (qk_import() < 0) {
        return NULL;
    }
    return PyModuleDef_Init(&moduledef);
}
