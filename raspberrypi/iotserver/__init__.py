import os

from flask import Flask

def create_app():
    app = Flask(__name__, instance_relative_config=True)

    # Se pasa un diccionario para configurar como clave-valor
    app.config.from_mapping(
        SECRET_KEY='dev',
        DATABASE=os.path.join(app.instance_path, 'iotserver.db')
    )

    try:
        # Crea el directorio "instance" donde se almacenan datos sensibles
        os.makedirs(app.instance_path)
    except OSError:
        pass

    from . import api
    app.register_blueprint(api.bp)

    return app