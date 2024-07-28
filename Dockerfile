# Utiliser l'image de base Ubuntu
FROM ubuntu:latest

# Mettre à jour les packages existants et installer Clang, la bibliothèque readline, sudo, valgrind, libbsd-dev, et d'autres outils nécessaires
RUN apt-get update && \
    apt-get install -y \
        clang \
        lldb \
        libreadline-dev \
        build-essential \
        sudo \
        valgrind \
        libbsd-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Copier le Makefile dans l'image
COPY Makefile .

# Commande par défaut pour garder le conteneur actif
CMD ["/bin/bash"]

