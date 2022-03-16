import imports
WIDTH, HEIGHT = 1400, 800 # window constant
WIN = pygame.display.set_mode((WIDTH, HEIGHT)) #create window
pygame.display.set_caption("space")
base_font = pygame.font.SysFont(None, 30)

#Background
BG = pygame.transform.scale(pygame.image.load(os.path.join("background-black.png")), (WIDTH-400, HEIGHT)) 

objects,G,dt = [],1,0.000001