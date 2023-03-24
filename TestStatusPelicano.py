import serial
from time import sleep

class CompleteTest(object):

    def __init__(self):

        self.trash = False
        self.door_open = False
        self.blocked = False
        self.ser = None
        self.opcion = 0
        self.puerto = 0

        self.CMDS = {
            'Factory_Disk_Motor_Off':           b'\x02\x04\x01\xff\x42\x56\x01\x10\x51',
            'Factory_Disk_Motor_Fwd':           b'\x02\x04\x01\xff\x42\x56\x01\x11\x50',
            'Factory_Disk_Motor_Rev':           b'\x02\x04\x01\xff\x42\x56\x01\x12\x4f',
            'Factory_Disk_Motor_Stop_Pos':      b'\x02\x04\x01\xff\x42\x56\x01\x15\x4c',
            'Factory_Trash_Motor_Off':          b'\x02\x04\x01\xff\x42\x56\x01\x20\x41',
            'Factory_Trash_Motor_Fwd':          b'\x02\x04\x01\xff\x42\x56\x01\x21\x40',
            'Factory_Trash_Motor_Rev':          b'\x02\x04\x01\xff\x42\x56\x01\x22\x3f',
            'Factory_Trash_Door_Small_Cycle':   b'\x02\x04\x01\xff\x42\x56\x01\x24\x3d',
            'Factory_Trash_Door_Comp_Cycle':    b'\x02\x04\x01\xff\x42\x56\x01\x25\x3c',
            'Enable':                           b"\x02\x02\x01\xE7\xFF\xFF\x16",
            'Clean bowl':                       b'\x02\x01\x01\xEF\x01\x0C',
            'Start motor':                      b"\x02\x01\x01\xE4\x01\x17",
            'Stop motor':                       b"\x02\x01\x01\xE4\x00\x18",
            'Self check':                       b'\x02\x00\x01\xe8\x15',
            'Simple poll':                      b'\x02\x00\x01\xFE\xFF',
            'Read opto states':                 b'\x02\x00\x01\xEC\x11',
            'Reset device':                     b"\x02\x00\x01\x01\xFC",
            'Read buffered':                    b"\x02\x00\x01\xE5\x18",
        }

        self.Fault_codes = {
            0: 'OK',
            1: 'Firmware corrupto',
            2: 'Falla en bobinas inductivas (sistema de medicion)',
            3: 'Falla en los sensores de credito',
            30: 'Bloque de datos del Checksum corrupto',
            253: 'Atasco de monedas en el sistema de medida',
            254: 'Disco bloqueado',
            255: 'Codigo de alarma no especificado',
        }

        self.Map_error = {
            0: 'NULL event, no error / previous error solved',
            1: 'uknown coin rejected',
            2: 'inhibited coin rejected',
            5: 'validation timeout',
            6: 'credit sensor timeout',
            14: 'sensor_blocked',
            17: 'coin going backwards',
            29: 'unexpected acceptance',
            30: 'unexpected rejectance',
            118: 'disco_detenido',
            119: 'change_rotational',
            255: 'unspecified alarm code',
        }

        self.Coins = {
            8: 1000,
            7: 500,
            6: 200,
            5: 100,
            4: 50,
            9: 50,
            10: 100,
            11: 200,
            12: 500,
        }

        self.main()

    def main(self):

        print("/------------------------------------------------------------------------/")
        print("Test para el validador pelicano")
        print("/------------------------------------------------------------------------/")
        print("Opcion 0. Corre la opcion 1 hasta la 7")
        print("Opcion 1. Revisa la comunicacion")
        print("Opcion 2. Corre una auto revision inicial")
        print("Opcion 3. Lee los opto estados")
        print("Opcion 4. Corre rutina de vaciado de basura")
        print("Opcion 5. Mueve el motor")
        print("Opcion 6. Corre auto revision final")
        print("Opcion 7. Resetea el dispositivo")
        print("Opcion 8. Lee las monedas en un ciclo infinito")
        print("/------------------------------------------------------------------------/")
        print("Cual opcion desea correr? (0-8)")

        try:
            self.opcion = int(input())
            if ((self.opcion >= 0) & (self.opcion <= 8)):
                pass
            else:
                print("Opcion invalida, ingrese un numero entre 0 y 8")
                return 1    
        except:
            print("Opcion invalida, ingrese un numero entero")
            return 1

        print("Por favor, introduzca el numero n del puerto serial donde esta conectado el pelicano /dev/ttyUSBn (Solo un numero entero): ")

        try:
            self.puerto = int(input())
        except:
            print("Puerto invalido, ingrese un numero entero")
            return 1

        try:
            self.ser = serial.Serial("/dev/ttyUSB"+str(self.puerto),9600,timeout=1)
        except Exception as e:
            print("El puerto no esta disponible, revise con el comando: ls /dev ",e)
            return 1

        self.opcion1()

        if self.opcion == 0:
            self.opcion2()
            self.opcion3()
            self.opcion4()
            self.opcion5()
            self.opcion6()
            self.opcion7()
        elif self.opcion == 2:
            self.opcion2()
        elif self.opcion == 3:
            self.opcion3()
        elif self.opcion == 4:
            self.trash = True
            self.opcion4()
        elif self.opcion == 5:
            self.opcion5()
        elif self.opcion == 6:
            self.opcion6()
        elif self.opcion == 7:
            self.opcion7()
        elif self.opcion == 8:
            self.opcion7()
            self.opcion8()
        
    def opcion1(self):

        print("")
        print("1. Revisando la comunicacion...")
        print("")

        self.ser.write(self.CMDS.get('Simple poll'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)

        try:
            if((rta[8] == 0)&(len(rta)==10)):
                print("Comunicacion OK")
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

    def opcion2(self):

        print("")
        print("2. Corriendo una auto-revision inicial...")
        print("")

        self.ser.write(self.CMDS.get('Self check'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)

        try:
            if(len(rta)==11):
                fault_code = rta[9]
                print("Codigo devuelto en la revision: ")
                print(self.Fault_codes.get(fault_code))
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

    def opcion3(self):

        print("")
        print("3. Leyendo los opto estados...")
        print("")

        self.ser.write(self.CMDS.get('Read opto states'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)
        
        try:
            if((len(rta)==11)):

                opto_states_str = format(rta[9],'04b')

                print("La lectura devuelve los siguientes 4 estados: ")
                if (opto_states_str[3] == '1'):
                    print("A) Hay algo en la bandeja de monedas")
                    self.trash = True
                else:
                    print("A) No hay nada en la bandeja de monedas")
                
                if (opto_states_str[2] == '1'):
                    print("B) La puerta de basura esta abierta")
                    self.door_open = True
                else:
                    print("B) La puerta de basura esta cerrada")

                if (opto_states_str[1] == '1'):
                    print("C) El sensor bajo esta bloqueado (Sensor de aceptacion y rechazo)")
                    self.blocked = True
                else:
                    print("C) El sensor bajo esta libre (Sensor de aceptacion y camino de rechazo)")

                if (opto_states_str[0] == '1'):
                    print("D) El sensor alto esta bloqueado (Sensor del camino de aceptacion)")
                    self.blocked = True
                else:
                    print("D) El sensor alto esta libre (Sensor del camino de aceptacion)")

                if (self.blocked):
                    print("--->>> Se recomienda revisar la salida de monedas del Pelicano, esta bloqueado !!!")

                if(self.door_open):
                    print("--->>> Se recomienda revisar nuevamente el pelicano para confirmar que se haya cerrado la puerta !!!")
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

    def opcion4(self):

        if (self.trash):
            print("")
            print("4. Corriendo rutina de vaciado de basura...")
            print("")

            self.ser.write(self.CMDS.get('Clean bowl'))
            sleep(0.1)
            rta = self.ser.read(self.ser.in_waiting)
            print(rta)
        
            try:
                if((len(rta) == 11)&(rta[9] == 0)):
                    print("Rutina de vaciado de basura corrida exitosamente")
                else:
                    print("Comunicacion mala o fallo en la respuesta")
                    print(list(rta))
                    return 1
            except:
                print("Fallo en la comunicacion, esta fue la respuesta:")
                print(list(rta))
                return 1

    def opcion5(self):

        print("")
        print("5. Moviendo motor por 4 segundos...")
        print("")

        if (self.blocked == False):

            self.ser.write(self.CMDS.get('Start motor'))
            sleep(0.1)
            rta = self.ser.read(self.ser.in_waiting)
            print(rta)
        
            try:
                if((len(rta) == 11)&(rta[9] == 0)):
                    print("Motor moviendose")
                else:
                    print("Comunicacion mala o fallo en la respuesta")
                    print(list(rta))
                    return 1
            except:
                print("Fallo en la comunicacion, esta fue la respuesta:")
                print(list(rta))
                return 1
            
            sleep(4)

            self.ser.write(self.CMDS.get('Stop motor'))
            sleep(0.1)
            rta = self.ser.read(self.ser.in_waiting)
            print(rta)

            try:
                if((len(rta) == 11)&(rta[9] == 0)):
                    print("Motor detenido")
                else:
                    print("Comunicacion mala o fallo en la respuesta")
                    print(list(rta))
                    return 1
            except:
                print("Fallo en la comunicacion, esta fue la respuesta:")
                print(list(rta))
                return 1
        else:
            print("No se pudo mover el motor porque los sensores estan bloqueados")

    def opcion6(self):

        print("")
        print("6. Corriendo auto revision final...")
        print("")

        self.ser.write(self.CMDS.get('Self check'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)
        
        try:
            if(len(rta)==11):
                fault_code = rta[9]
                print("Codigo devuelto en la revision: ")
                print(self.Fault_codes.get(fault_code))
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

    def opcion7(self):

        print("")
        print("7. Reseteando el dispositivo...")
        print("")

        self.ser.write(self.CMDS.get('Reset device'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)
        
        try:
            if((len(rta) == 10)&(rta[8] == 0)):
                print("Eventos borrados")
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

    def opcion8(self):

        print("")
        print("8. Leyendo monedas...")
        print("")

        self.ser.write(self.CMDS.get('Enable'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)
        
        try:
            if((len(rta) == 12)&(rta[10] == 0)):
                print("Todos los canales habilitados")
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

        stop = False

        print("Comienza ciclo de lectura de monedas")

        self.ser.write(self.CMDS.get('Start motor'))
        sleep(0.1)
        rta = self.ser.read(self.ser.in_waiting)
        print(rta)
        
        try:
            if((len(rta) == 11)&(rta[9] == 0)):
                print("Motor moviendose")
            else:
                print("Comunicacion mala o fallo en la respuesta")
                print(list(rta))
                return 1
        except:
            print("Fallo en la comunicacion, esta fue la respuesta:")
            print(list(rta))
            return 1

        Evento = 0
        error = False
        
        while(stop == False):

            self.ser.write(self.CMDS.get('Read buffered'))
            sleep(0.1)
            rta = self.ser.read(self.ser.in_waiting)

            if((len(rta) == 21)&(rta[9] != Evento)):
                
                print("")
                print("Evento numero: ",rta[9])
                print(list(rta))

                if ((rta[10] == 0)&(rta[11] != 0)):
                    print("Ocurrio un error: ")
                    error = True
                    if (self.Map_error.get(rta[11]) == None):
                        print("Codigo de error desconocido: ",rta[11])
                    else:
                        print(self.Map_error.get(rta[11]))

                elif (rta[10] != 0):

                    if (self.Coins.get(rta[10]) == None):
                        print("Moneda desconocida: ",rta[10])
                    else:
                        print("Moneda de",self.Coins.get(rta[10]),"detectada")

                    if (rta[11] == 1):
                        print("Aceptada")
                    else:
                        print("No aceptada")                 
                
                if ((rta[10] == 0)&(rta[11] == 0)&(error == True)):
                    print("Ultimo error solucionado")
                    error = False

                Evento = rta[9]

CompleteTest()


'''
def simplecomm(header):

import serial
ser = serial.Serial("/dev/ttyUSB0",9600,timeout=1)
from time import sleep

Dest_addr = 2
Sour_addr = 1
Data = 0
Header = 236
Chk = 256-((Dest_addr+Sour_addr+Data+Header)%256)

Dest_addr = Dest_addr.to_bytes(1,'big')
Sour_addr = Sour_addr.to_bytes(1,'big')
Data = Data.to_bytes(1,'big')
Header = Header.to_bytes(1,'big')
Chk = Chk.to_bytes(1,'big')

Cmd = Dest_addr+Data+Sour_addr+Header+Chk

ser.write(Cmd)
print("Este es el comando: ",Cmd)
sleep(0.1)
rta = ser.read_all()
print("Esta es la rta: ",rta)

def factory255(ID):

    Dest_addr = 2
    Sour_addr = 1
    Data = 4
    Data1=66
    Data2=86
    Data3=1
    Data4=ID
    Header = 255
    Chk = 256-((Dest_addr+Sour_addr+Data+Header+Data1+Data2+Data3+Data4)%256)

    Dest_addr = Dest_addr.to_bytes(1,'big')
    Sour_addr = Sour_addr.to_bytes(1,'big')
    Data = Data.to_bytes(1,'big')
    Header = Header.to_bytes(1,'big')
    Data1 = Data1.to_bytes(1,'big')
    Data2 = Data2.to_bytes(1,'big')
    Data3 = Data3.to_bytes(1,'big')
    Data4 = Data4.to_bytes(1,'big')
    Chk = Chk.to_bytes(1,'big')

    Cmd = Dest_addr+Data+Sour_addr+Header+Data1+Data2+Data3+Data4+Chk

    ser.write(Cmd)
    print("Este es el comando: ",Cmd)
    sleep(0.1)
    rta = ser.read_all()
    print("Esta es la rta: ",rta)

def testmotors239(comm,speed=None):

    Dest_addr = 2
    Sour_addr = 1
    if (speed != None):
        Data = 2
        Data2 = speed
    else:
        Data = 1
        Data2 = 0

    Data1 = comm
    Header = 239
    Chk = 256-((Dest_addr+Sour_addr+Data+Header+Data1+Data2)%256)

    Dest_addr = Dest_addr.to_bytes(1,'big')
    Sour_addr = Sour_addr.to_bytes(1,'big')
    Data = Data.to_bytes(1,'big')
    Header = Header.to_bytes(1,'big')
    Data1 = Data1.to_bytes(1,'big')
    Chk = Chk.to_bytes(1,'big')

    if (speed != None):
        Data2 = Data2.to_bytes(1,'big')
        Cmd = Dest_addr+Data+Sour_addr+Header+Data1+Data2+Chk
    else:
        Cmd = Dest_addr+Data+Sour_addr+Header+Data1+Chk

    ser.write(Cmd)
    print("Este es el comando: ",Cmd)
    sleep(0.1)
    rta = ser.read_all()
    print("Esta es la rta: ",rta)

def movingmotor(onoff):

    Dest_addr = 2
    Sour_addr = 1
    Data = 1
    Data1 = onoff
    Header = 228
    Chk = 256-((Dest_addr+Sour_addr+Data+Data1+Header)%256)

    Dest_addr = Dest_addr.to_bytes(1,'big')
    Sour_addr = Sour_addr.to_bytes(1,'big')
    Data = Data.to_bytes(1,'big')
    Data1 = Data1.to_bytes(1,'big')
    Header = Header.to_bytes(1,'big')
    Chk = Chk.to_bytes(1,'big')

    Cmd = Dest_addr+Data+Sour_addr+Header+Data1+Chk

    ser.write(Cmd)
    print("Este es el comando: ",Cmd)
    sleep(0.1)
    rta = ser.read_all()
    print("Esta es la rta: ",rta)

def testsolenoids(mask):

    Dest_addr = 2
    Sour_addr = 1
    Data = 1
    Data1 = mask
    Header = 240
    Chk = 256-((Dest_addr+Sour_addr+Data+Data1+Header)%256)

    Dest_addr = Dest_addr.to_bytes(1,'big')
    Sour_addr = Sour_addr.to_bytes(1,'big')
    Data = Data.to_bytes(1,'big')
    Data1 = Data1.to_bytes(1,'big')
    Header = Header.to_bytes(1,'big')
    Chk = Chk.to_bytes(1,'big')

    Cmd = Dest_addr+Data+Sour_addr+Header+Data1+Chk

    ser.write(Cmd)
    print("Este es el comando: ",Cmd)
    sleep(0.2)
    rta = ser.read_all()
    print("Esta es la rta: ",rta)

'''

#240 test solenoids