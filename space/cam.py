class Camera:
    def __init__(self, x, y, scale):
        self.x = x
        self.y = y
        self.scale = scale
    def move(self):
            keys = pygame.key.get_pressed()
            if keys[pygame.K_LEFT] : # left
                self.x -= 5
            if keys[pygame.K_RIGHT] : # right
                self.x += 5
            if keys[pygame.K_UP] : # up
                self.y -= 5
            if keys[pygame.K_DOWN] : # down
                self.y += 5
    def zoom(self, event):
        if event.type == pygame.MOUSEWHEEL: #scale 
                    self.scale += 100000*event.y/((WIDTH-200)*HEIGHT)
cam = Camera(0, 0, 1) #cretae cam
class Interface:
    def __init__(self, info, x, y, color, thick):
        self.x = x
        self.y = y
        self.w = 200
        self.h = 30
        self.value = ''
        self.input_rect = pygame.Rect(self.x, self.y, self.w, self.h)
        self.color = color
        self.thick = thick #толщина/заливка
        self.info = base_font.render("{:>10s}".format(info), True, 'red')
        self.active = False
        
    def draw(self, window):
        pygame.draw.rect(window, self.color, self.input_rect, self.thick)
        window.blit(self.info, (self.input_rect.x - 100, self.input_rect.y + 5))
        self.text_surface = base_font.render(self.value, True, self.color)
        window.blit(self.text_surface, (self.input_rect.x + 5, self.input_rect.y + 5))
        self.input_rect.w = max(self.w, self.text_surface.get_width() + 10)

fields = [Interface('X:',WIDTH-300, 30, 'white', 2),
               Interface('Y:',WIDTH-300, 90, 'white', 2),
               Interface('M:',WIDTH-300, 150, 'white', 2),
               Interface('Speed:',WIDTH-300, 210, 'white', 2),
               Interface('Direct:',WIDTH-300, 270, 'white', 2),
               Interface('Color:',WIDTH-300, 330, 'white', 2)]

spawn_button = Interface('Spawn:',WIDTH-300, 510, 'yellow', 0)
delete_button = Interface('Delete:',WIDTH-300, 670, 'red', 0)

class Object:

    def __init__(self, x, y, m, vX, vY, color):
        self.x = x
        self.y = y
        self.fX = 0
        self.fY = 0
        self.vX = vX
        self.vY = vY
        self.m = m
        self.color = color
        self.radius = math.sqrt(self.m / 1000)

    def draw(self, window):
        pygame.draw.circle(window, self.color, ((self.x - cam.x)*cam.scale + WIDTH/2-200, (self.y - cam.y)*cam.scale + HEIGHT/2), self.radius*cam.scale)

    def join(self,secob):
        # create new circle with new parametr
        self.vX=(secob.vX*secob.m+self.vX*self.m)/(self.m+secob.m)
        self.vY = (secob.vY * secob.m + self.vY * self.m) / (self.m + secob.m)
        self.x = (self.x*self.m+secob.x*secob.m)/(self.m+secob.m)
        self.y = (self.y * self.m + secob.y * secob.m) / (self.m + secob.m)
        self.m += secob.m
        self.radius = math.sqrt(self.m / 1000)
        objects.remove(secob)
        self.fX=0
        self.fY=0

    def force_calculate(self, secob,dx,dy):
        r = math.sqrt(dx * dx + dy * dy)
        if (r > 0):
            m1 = self.m
            m2 = secob.m
            sin = dy / r
            cos = dx / r
            f = G * (m1 * m2) / (r * r) 
            self.fX += f * cos
            self.fY += f * sin

    def calculate(self):
        for object in objects:
            dx,dy = object.x - self.x,object.y - self.y
            r = math.sqrt(dx * dx + dy * dy)
            self.force_calculate(object, dx, dy)
            if (r<self.radius+object.radius) and self.m>=object.m and self != object:
                self.join(object)
                for object in objects:
                    dx,dy = object.x - self.x,object.y - self.y
                    self.force_calculate(object, dx, dy)
            
        self.vX += self.fX / self.m * dt
        self.vY += self.fY / self.m * dt

    def move(self):
        self.x += self.vX * dt
        self.y += self.vY * dt