void PostFlow_input(int time){

  FILE *fpr;
  char fn[64];
  int i, j, r0, n, xi, eta, ns, nv;
  int Sij;
  int num;
  double mach, alp, re, Qt;
  int istep;

  for(n=0;n<NT;n++){
    sprintf(fn,"./out_wcns2/postFlow[%d][%d]",n,time);
    fpr = fopen(fn,"rb");

    if(NULL==fpr){
      perror(fn);
      exit(1);
    }

    num = sizeof(int) * 2;
    xi  = it[n] - 1;
    eta = jt[n] - 1;

    fread(&num,sizeof(int),1,fpr);
    fread(&xi,sizeof(int),1,fpr);
    fread(&eta,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);

    num = sizeof(double) * 3 + sizeof(int) * 1;
    mach = 0.0;
    alp = 0.0;
    re = 0.0;
    istep = 0;

    fread(&num,sizeof(int),1,fpr);
    fread(&mach,sizeof(double),1,fpr);
    fread(&alp,sizeof(double),1,fpr);
    fread(&re,sizeof(double),1,fpr);
    fread(&istep,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    Sij = xi * eta;
    num = sizeof(double) * 4 * Sij;

    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&rho[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&ux[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&uy[n][r0],sizeof(double),1,fpr);
      }
    }
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&e[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);

    fread(&num,sizeof(int),1,fpr);
    fread(&ns,sizeof(int),1,fpr);
    fread(&nv,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&k_turb[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&omega[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fread(&Mut[n][r0],sizeof(double),1,fpr);
      }
    }
    fread(&num,sizeof(int),1,fpr);

    fread(&num,sizeof(int),1,fpr);
    fread(&num,sizeof(int),1,fpr);


    fclose(fpr);

  }

  for(n=0;n<NT;n++){

    /*************速度に変換************************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	ux[n][r0] = ux[n][r0] / rho[n][r0];
	uy[n][r0] = uy[n][r0] / rho[n][r0];
	p[n][r0] = Cons_calcP(n, r0);
      }
    }
    
    
    /*************保存量の計算************************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	Q[n][0][r0] = rho[n][r0] * S[n][r0];
	Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
	Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
	Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }
    
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	TurbQ[n][0][r0] = rho[n][r0] * k_turb[n][r0] * S[n][r0];
	TurbQ[n][1][r0] = rho[n][r0] * omega[n][r0] * S[n][r0];
      }
    }
  }


}
