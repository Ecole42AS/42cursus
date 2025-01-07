

import django.db.models.deletion
from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='GameSession',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('player1_id', models.IntegerField(blank=True, null=True)),
                ('player2_id', models.IntegerField(blank=True, null=True)),
                ('score_player1', models.IntegerField(default=0)),
                ('score_player2', models.IntegerField(default=0)),
                ('winner_id', models.IntegerField(blank=True, null=True)),
                ('pong_game_id', models.IntegerField(blank=True, null=True)),
                ('is_active', models.BooleanField(default=True)),
                ('created_at', models.DateTimeField(auto_now_add=True)),
                ('start_time', models.DateTimeField(blank=True, null=True)),
                ('duration', models.IntegerField(default=60)),
                ('ended_at', models.DateTimeField(blank=True, null=True)),
            ],
        ),
        migrations.CreateModel(
            name='Tournament',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=255, unique=True)),
                ('creator_id', models.IntegerField(blank=True, null=True)),
                ('players', models.JSONField(default=list)),
                ('winner_id', models.IntegerField(blank=True, null=True)),
                ('created_at', models.DateTimeField(auto_now_add=True)),
            ],
        ),
        migrations.CreateModel(
            name='TournamentMatch',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('player1_id', models.IntegerField(blank=True, null=True)),
                ('player2_id', models.IntegerField(blank=True, null=True)),
                ('winner_id', models.IntegerField(blank=True, null=True)),
                ('is_completed', models.BooleanField(default=False)),
                ('scheduled_at', models.DateTimeField()),
                ('tournament', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='game.tournament')),
            ],
        ),
    ]
